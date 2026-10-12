#include "support/boot_host.h"
#include "check.h"

int main(void)
{
    boot_keep_feed_override = true;
    const char program[] = { CMD_OVERRIDE_FEED_COARSE_PLUS, CMD_RESET, '$', 'G', '\n', 0 };
    boot_program = program;
    CHECK(grbl_enter() == 0);
    CHECK(boot_feed_before_reset == 110);
    CHECK(sys.override.feed_rate == 110);
    return EXIT_SUCCESS;
}
