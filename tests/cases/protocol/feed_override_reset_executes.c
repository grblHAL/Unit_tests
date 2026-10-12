#include "support/protocol_host.h"
#include "check.h"

int main(void)
{
    prepare_protocol();
    execute_command(CMD_OVERRIDE_FEED_COARSE_MINUS);
    CHECK(sys.override.feed_rate == 90);
    execute_command(CMD_OVERRIDE_FEED_RESET);
    CHECK(sys.override.feed_rate == 100);
    return EXIT_SUCCESS;
}
