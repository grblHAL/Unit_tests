#include "support/stop_motion_host.h"
int main(void)
{
    start_stop_motion();
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_FEED_COARSE_PLUS));
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_COARSE_PLUS));
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_COOLANT_FLOOD_TOGGLE));
    stop_program();
    CHECK(get_feed_override() == 0 && get_spindle_override() == 0 && get_coolant_override() == 0);
    CHECK(sys.override.feed_rate == 100);
    CHECK(sys.override_delay.flags == 0 && !sys.flags.feed_hold_pending);
    return EXIT_SUCCESS;
}
