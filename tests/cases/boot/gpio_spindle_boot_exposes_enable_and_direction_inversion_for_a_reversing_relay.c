#include "support/boot_gpio_spindle_host.h"
int main(void)
{
    run_gpio_spindle_options(true);
    return EXIT_SUCCESS;
}
