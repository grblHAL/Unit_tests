#include "support/protocol_host.h"
#include "check.h"

int main(void)
{
    prepare_protocol();
    execute_command(CMD_OVERRIDE_RAPID_MEDIUM);
    CHECK(sys.override.rapid_rate == RAPID_OVERRIDE_MEDIUM);
    execute_command(CMD_OVERRIDE_RAPID_LOW);
    CHECK(sys.override.rapid_rate == RAPID_OVERRIDE_LOW);
    execute_command(CMD_OVERRIDE_RAPID_RESET);
    CHECK(sys.override.rapid_rate == 100);
    CHECK(sys.override.feed_rate == 100);
    return EXIT_SUCCESS;
}
