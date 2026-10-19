#include "support/boot_debug_uart_host.h"
int main(void)
{
    run_boot_debug_uart(true);
    return EXIT_SUCCESS;
}
