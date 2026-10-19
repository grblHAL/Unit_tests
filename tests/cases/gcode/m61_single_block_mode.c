#include "support/boot_program_pause_host.h"
int main(void)
{
    pause_single_block = true;
    run_boot_program_pause("", false, true);
    CHECK(!sys.flags.single_block);
    return EXIT_SUCCESS;
}
