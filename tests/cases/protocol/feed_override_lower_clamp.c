#include "support/protocol_host.h"
#include "check.h"

int main(void)
{
    prepare_protocol();
    for(unsigned command = 0; command < 30; command++)
        execute_command(CMD_OVERRIDE_FEED_COARSE_MINUS);
    CHECK(sys.override.feed_rate == MIN_FEED_RATE_OVERRIDE);
    CHECK(get_feed_override() == 0);
    return EXIT_SUCCESS;
}
