#include "support/laser_stepper_host.h"
#include "support/parking_host.h"

static bool sleeping;
static message_code_t (*sleep_feedback)(message_code_t);
static message_code_t observe_sleep(message_code_t message)
{
    if(message == Message_SleepMode) sleeping = true;
    return sleep_feedback(message);
}

int main(void)
{
    prepare_pwm_stepper_mode(Mode_Standard);
    configure_parking_move();
    report_init_fns();
    hal.coolant_cap.flood = true;
    settings.safety_door.flags.keep_coolant_on = true;
    sys.cold_start = false;
    sys.driver_started = true;
    queue_motion_program("G0Z0");
    execute_motion_program();
    CHECK(protocol_exec_rt_system());
    unsigned z_pulses = axis_pulses[Z_AXIS];
    CHECK(state_get() == STATE_IDLE && physical_position[Z_AXIS] == 0);
    CHECK(laser_block("M3S500") == Status_OK);
    CHECK(laser_block("M8") == Status_OK);
    CHECK(laser_output_state.on && parking_coolant.flood);
    char enable[] = "$62=1", command[] = "$SLP";
    CHECK(system_execute_line(enable, hal.stream.write) == Status_OK);
    sleep_feedback = grbl.report.feedback_message;
    grbl.report.feedback_message = observe_sleep;
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    for(unsigned tick = 0; tick < 200000 && !sleeping; tick++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
        CHECK(protocol_exec_rt_system());
    }
    CHECK(sleeping && state_get() == STATE_SLEEP);
    CHECK(!laser_output_state.on && !parking_coolant.value);
    CHECK(physical_position[Z_AXIS] == 0 && axis_pulses[Z_AXIS] == z_pulses);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Y_AXIS] == 0);
    CHECK(!sys.step_control.execute_sys_motion && plan_get_current_block() == NULL);
    CHECK(strstr(engine_output, "Sleeping") != NULL);
    return EXIT_SUCCESS;
}
