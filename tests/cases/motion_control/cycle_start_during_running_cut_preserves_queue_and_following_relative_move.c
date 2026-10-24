#include "support/jog_motion_host.h"
int main(void)
{
    prepare_jog_motion();
    sys.cold_start = false;
    sys.driver_started = true;
    queue_motion_program("G1X20F100");
    queue_motion_program("G91G1X1");
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    unsigned starts = 0;
    for(unsigned ticks = 0; ticks < 100000 && state_get() != STATE_IDLE; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
        bool press = starts == 0 ? axis_pulses[X_AXIS] >= 16 :
                     starts == 1 && axis_pulses[X_AXIS] >= 1616;
        if(press) {
            CHECK(state_get() == STATE_CYCLE);
            plan_block_t *current = plan_get_current_block();
            CHECK(current != NULL);
            int32_t before = physical_position[X_AXIS];
            CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
            CHECK(protocol_exec_rt_system());
            CHECK(state_get() == STATE_CYCLE && !sys.suspend);
            CHECK(plan_get_current_block() == current);
            CHECK(physical_position[X_AXIS] == before && wake_calls == 1);
            starts++;
        }
        CHECK(protocol_exec_rt_system());
    }
    CHECK(starts == 2 && wake_calls == 1);
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(axis_pulses[X_AXIS] == 1680 && physical_position[X_AXIS] == 1680);
    CHECK(sys.position[X_AXIS] == 1680);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    NEAR(gc_state.position[X_AXIS], 21);
    CHECK(sys.alarm == Alarm_None && !sys.abort && !sys.position_lost);
    return EXIT_SUCCESS;
}
