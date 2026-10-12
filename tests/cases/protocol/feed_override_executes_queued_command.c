#include "support/protocol_host.h"
#include "check.h"

int main(void)
{
    prepare_protocol();
    execute_command(CMD_OVERRIDE_FEED_COARSE_PLUS);
    CHECK(sys.override.feed_rate == 110);
    CHECK(sys.override.rapid_rate == 100);
    CHECK(get_feed_override() == 0);
    return EXIT_SUCCESS;
}
