#include "support/boot_fault_loop_host.h"
int main(void)
{
    boot_setup_success = false;
    observe_fault_startup(1);
    return EXIT_FAILURE;
}
