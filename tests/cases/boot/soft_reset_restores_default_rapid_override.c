#include "support/boot_host.h"
#include "check.h"

int main(void)
{
    const char program[] = { CMD_OVERRIDE_RAPID_MEDIUM, CMD_RESET, '$', 'G', '\n', 0 };
    boot_program = program;
    CHECK(grbl_enter() == 0);
    CHECK(boot_rapid_before_reset == 50);
    CHECK(sys.override.rapid_rate == 100);
    return EXIT_SUCCESS;
}
