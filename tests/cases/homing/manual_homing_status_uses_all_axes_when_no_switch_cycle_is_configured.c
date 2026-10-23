#include "support/homing_command_host.h"
#include "ngc_params.h"
static void check_manual_homed_report(bool complete)
{
    char state_name[] = "_homed_state", axes_name[] = "_homed_axes";
    float value;
    CHECK(ngc_named_param_get(state_name, &value)); NEAR(value, complete ? 1 : 0);
    CHECK(ngc_named_param_get(axes_name, &value)); NEAR(value, complete ? AXES_BITMASK : 0);
    status_report_tracking_t tracking = {.flags = {.homed = true}};
    engine_output[0] = '\0';
    report_realtime_status(hal.stream.write, &tracking);
    CHECK(strstr(engine_output, complete ? "|H:1" : "|H:0") != NULL);
    CHECK(strstr(engine_output, complete ? "|H:1," : "|H:0,") == NULL);
}
int main(void)
{
    prepare_homing_command();
    char mode[] = "41"; /* Enabled, origin at zero, manual; no single-axis commands. */
    CHECK(settings_store_setting(Setting_HomingEnable, mode) == Status_OK);
    for(unsigned slot = 0; slot < N_AXIS; slot++) {
        char empty[] = "0";
        CHECK(settings_store_setting(Setting_HomingCycle_1 + slot, empty) == Status_OK);
    }
    CHECK(settings.homing.flags.manual && !settings.homing.flags.single_axis_commands);
    CHECK(sys.homing.mask == 0);
    queue_motion_program("G0X1Y2Z3");
    execute_motion_program();
    CHECK(protocol_exec_rt_system());
    CHECK(sys.homed.mask == 0);
    check_manual_homed_report(false);
    CHECK(execute_homing_command("$H") == Status_OK);
    CHECK(sys.homed.mask == AXES_BITMASK);
    check_manual_homed_report(true);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(sys.position[axis] == 0);
        CHECK(physical_position[axis] == (int32_t)(80 * (axis + 1)));
        CHECK(axis_pulses[axis] == 80 * (axis + 1));
    }
    CHECK(wake_calls == 1 && completed_calls == 1 && homing_success);
    CHECK(limit_enable_calls == 0 && !sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
