#include "support/protocol_host.h"
int main(void)
{
    prepare_protocol();
    execute_command(CMD_OVERRIDE_FEED_COARSE_PLUS);
    CHECK(sys.override.feed_rate == 110);
    execute_command(CMD_OVERRIDE_RAPID_EXTRA_LOW);
    CHECK(sys.override.rapid_rate == RAPID_OVERRIDE_EXTRA_LOW);
    CHECK(sys.override.feed_rate == 110);
    execute_command(CMD_OVERRIDE_RAPID_RESET);
    CHECK(sys.override.rapid_rate == DEFAULT_RAPID_OVERRIDE);
    CHECK(sys.override.feed_rate == 110);
    return EXIT_SUCCESS;
}
