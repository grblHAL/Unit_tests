#include "support/hold_host.h"
#include "support/report_host.h"
int main(void)
{
    start_hold_move();
    report_init();
    hal.stream.is_connected = connected; hal.coolant.get_state = coolant_state;
    CHECK(protocol_enqueue_realtime_command(CMD_FEED_HOLD));
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_HOLD && sys.holding_state == Hold_Pending);
    engine_output[0] = '\0'; realtime_report();
    CHECK(strncmp(engine_output, "<Hold:1|", 8) == 0);
    finish_motion_pulses(); CHECK(protocol_exec_rt_system());
    CHECK(sys.holding_state == Hold_Complete && sys.suspend);
    engine_output[0] = '\0'; realtime_report();
    CHECK(strncmp(engine_output, "<Hold:0|", 8) == 0);
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system()); finish_motion_pulses();
    CHECK(sys.position[X_AXIS] == 1600 && axis_pulses[X_AXIS] == 1600);
    return EXIT_SUCCESS;
}
