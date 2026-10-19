#include "support/soft_limit_motion_host.h"
int main(void)
{
    prepare_soft_limit_motion();
    queue_motion_program("G1X-20F100");
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    for(unsigned ticks = 0; ticks < 100; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
    CHECK(axis_pulses[X_AXIS] > 0 && axis_pulses[X_AXIS] < 1600);
    soft_reset_during_hold = true;
    float target[N_AXIS] = {-60};
    plan_line_data_t data;
    plan_data_init(&data);
    data.feed_rate = 100;
    CHECK(mc_line(target, &data) == Status_Aborted);
    CHECK(soft_hold_seen && soft_hold_reset_sent);
    CHECK(sys.abort && sys.position_lost && sys.alarm == Alarm_AbortCycle);
    CHECK(!soft_alarm_seen && !soft_status_requested);
    CHECK(strstr(engine_output, "ALARM:3") != NULL);
    CHECK(strstr(engine_output, "ALARM:2") == NULL);
    CHECK(!st_is_stepping() && axis_pulses[X_AXIS] < 1600);
    CHECK(sys.position[X_AXIS] == physical_position[X_AXIS]);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
