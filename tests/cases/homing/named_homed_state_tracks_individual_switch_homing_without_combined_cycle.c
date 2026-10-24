#include "support/homing_command_host.h"
#include "support/named_parameter_host.h"

static void check_named_homing(unsigned axes, bool complete)
{
    NEAR(read_named_parameter("_homed_axes"), axes);
    NEAR(read_named_parameter("_homed_state"), complete ? 1 : 0);
    status_report_tracking_t tracking = {.flags = {.homed = true}};
    char expected[16];
    snprintf(expected, sizeof(expected), "|H:%u,%u", complete ? 1u : 0u, axes);
    engine_output[0] = '\0';
    report_realtime_status(hal.stream.write, &tracking);
    CHECK(strstr(engine_output, expected) != NULL);
}

int main(void)
{
    prepare_homing_command();
    char mode[] = "3"; // Enabled with individual-axis commands; no manual origin setting.
    CHECK(settings_store_setting(Setting_HomingEnable, mode) == Status_OK);
    for(unsigned slot = 0; slot < N_AXIS; slot++) {
        char empty[] = "0";
        CHECK(settings_store_setting(Setting_HomingCycle_1 + slot, empty) == Status_OK);
    }
    CHECK(sys.homing.mask == 0 && settings.homing.flags.single_axis_commands);
    CHECK(!settings.homing.flags.manual);
    check_named_homing(0, false);
    CHECK(execute_homing_command("$HX") == Status_OK);
    check_named_homing(X_AXIS_BIT, false);
    CHECK(physical_position[X_AXIS] == 70 && axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(protocol_exec_rt_system());
    CHECK(execute_homing_command("$HY") == Status_OK);
    check_named_homing(X_AXIS_BIT | Y_AXIS_BIT, false);
    CHECK(physical_position[Y_AXIS] == 110 && axis_pulses[Z_AXIS] == 0);
    CHECK(protocol_exec_rt_system());
    CHECK(execute_homing_command("$HZ") == Status_OK);
    check_named_homing(AXES_BITMASK, true);
    CHECK(physical_position[Z_AXIS] == 150 && completed_calls == 3 && homing_success);
    CHECK(plan_get_current_block() == NULL && state_get() == STATE_IDLE);
    CHECK(reset_calls == 0 && !sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
