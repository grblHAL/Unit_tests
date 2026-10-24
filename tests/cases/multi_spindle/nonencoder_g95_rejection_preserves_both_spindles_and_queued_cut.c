#include "support/multi_spindle_hold_motion_host.h"
int main(void)
{
    prepare_multi_spindle_modal_program();
    hal.coolant.get_state = multi_hold_coolant;
    hal.f_step_timer = 1000000;
    hal.stepper.enable = enable_motors;
    hal.stepper.go_idle = idle_driver;
    hal.stepper.wake_up = wake_driver;
    hal.stepper.cycles_per_tick = timer_cycles;
    hal.stepper.pulse_start = pulse_driver;
    st_reset();
    start_two_modal_spindles();
    queue_motion_program("G1X20F100");
    plan_block_t *cut = plan_get_current_block();
    unsigned outputs[2] = {spindle_output_calls[0], spindle_output_calls[1]};
    const char *unsupported[] = {"G95F0.2$1", "G95F0.2$0"};
    for(unsigned i = 0; i < sizeof(unsupported) / sizeof(unsupported[0]); i++) {
        CHECK(spindle_program_block(unsupported[i]) == Status_GcodeUnsupportedCommand);
        CHECK(gc_state.modal.feed_mode == FeedMode_UnitsPerMin);
        NEAR(gc_state.feed_rate, 100);
        CHECK(plan_get_current_block() == cut);
        CHECK(spindle_output_calls[0] == outputs[0] && spindle_output_calls[1] == outputs[1]);
        CHECK(actual_spindle_states[0].on && !actual_spindle_states[0].ccw);
        CHECK(actual_spindle_states[1].on && actual_spindle_states[1].ccw);
        NEAR(actual_spindle_rpm[0], 3000);
        NEAR(actual_spindle_rpm[1], 7000);
    }
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(physical_position[X_AXIS] == 1600 && sys.position[X_AXIS] == 1600);
    CHECK(axis_pulses[X_AXIS] == 1600 && axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
