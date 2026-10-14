#include "support/boot_fault_loop_host.h"
int main(void)
{
    boot_init_success = false;
    observe_fault_startup(0);
    return EXIT_FAILURE;
}
