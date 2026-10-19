#include "support/boot_program_pause_host.h"
int main(void)
{
    run_boot_program_pause("M1", true, false);
    return EXIT_SUCCESS;
}
