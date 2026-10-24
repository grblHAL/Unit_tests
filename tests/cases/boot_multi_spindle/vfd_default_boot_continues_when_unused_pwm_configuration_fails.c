#include "support/boot_vfd_default_host.h"
int main(void)
{
    unused_pwm_unavailable = true;
    run_vfd_default_boot(false);
    CHECK(!spindle_is_enabled(1));
    return EXIT_SUCCESS;
}
