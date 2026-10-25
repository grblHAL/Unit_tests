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
    CHECK(spindle_program_block("G90G21G1F250") == Status_OK);
    unsigned primary_writes = spindle_output_calls[0];
    char invalid[] = "$J=G92X1F100";
    CHECK(system_execute_line(invalid, hal.stream.write) == Status_InvalidJogCommand);
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL && wake_calls == 0);
    CHECK(physical_position[X_AXIS] == 0 && axis_pulses[X_AXIS] == 0);
    CHECK(!gc_state.modal.distance_incremental);
    NEAR(gc_state.feed_rate, 250);
    char jog[] = "$J=G91G21X1F100";
    CHECK(system_execute_line(jog, hal.stream.write) == Status_OK);
    CHECK(state_get() == STATE_JOG && wake_calls == 1);
    plan_block_t *block = plan_get_current_block();
    CHECK(block != NULL && block->condition.jog_motion);
    CHECK(block->spindle.hal == spindle_get(1));
    NEAR(block->spindle.rpm, 7000);
    CHECK(!gc_state.modal.distance_incremental && gc_state.modal.motion == MotionMode_Linear);
    NEAR(gc_state.feed_rate, 250);
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(physical_position[X_AXIS] == 80 && sys.position[X_AXIS] == 80);
    CHECK(axis_pulses[X_AXIS] == 80 && axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(actual_spindle_states[0].on && !actual_spindle_states[0].ccw);
    CHECK(actual_spindle_states[1].on && actual_spindle_states[1].ccw);
    NEAR(actual_spindle_rpm[0], 3000); NEAR(actual_spindle_rpm[1], 7000);
    CHECK(spindle_output_calls[0] == primary_writes);
    CHECK(!gc_state.modal.distance_incremental);
    NEAR(gc_state.feed_rate, 250);
    NEAR(gc_state.position[X_AXIS], 1);
    return EXIT_SUCCESS;
}
