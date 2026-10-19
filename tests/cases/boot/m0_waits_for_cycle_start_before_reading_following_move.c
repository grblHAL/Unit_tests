#include "support/boot_program_pause_host.h"
int main(void)
{
    run_boot_program_pause("M0", false, true);
    return EXIT_SUCCESS;
}
