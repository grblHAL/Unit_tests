#include "support/boot_program_pause_host.h"
int main(void)
{
    run_boot_program_pause("M0", true, true);
    CHECK(!sys.suspend && state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
