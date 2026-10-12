#include "support/protocol_host.h"
#include "check.h"

int main(void)
{
    prepare_protocol();
    sys.override_delay.feedrate = true;
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_FEED_COARSE_PLUS));
    CHECK(protocol_exec_rt_system());
    CHECK(sys.override.feed_rate == 100);
    sys.override_delay.feedrate = false;
    CHECK(protocol_exec_rt_system());
    CHECK(sys.override.feed_rate == 110);
    CHECK(get_feed_override() == 0);
    return EXIT_SUCCESS;
}
