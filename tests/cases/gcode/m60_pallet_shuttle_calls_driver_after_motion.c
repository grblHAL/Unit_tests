#include "support/boot_program_pause_host.h"
int main(void)
{
    pause_use_pallet = true;
    run_boot_program_pause("M60", false, true);
    CHECK(pause_pallet_calls == 1);
    return EXIT_SUCCESS;
}
