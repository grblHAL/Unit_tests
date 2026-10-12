#include "support/protocol_host.h"
#include "check.h"

int main(void)
{
    prepare_protocol();
    execute_command(CMD_OVERRIDE_FEED_FINE_PLUS);
    CHECK(sys.override.feed_rate == 101);
    execute_command(CMD_OVERRIDE_FEED_FINE_MINUS);
    CHECK(sys.override.feed_rate == 100);
    return EXIT_SUCCESS;
}
