#include "support/boot_host.h"
#include "check.h"

int main(void)
{
    const char program[] = { CMD_OVERRIDE_FEED_COARSE_PLUS, CMD_RESET, '$', 'G', '\n', 0 };
    boot_program = program;
    CHECK(grbl_enter() == 0);
    CHECK(boot_feed_before_reset == 110);
    CHECK(sys.override.feed_rate == 100);
    return EXIT_SUCCESS;
}
