#include "tmc_host.h"
int main(void)
{
    tmc_prepare();
    tmc_start();
    CHECK(!tmc_drivers[0]->get_en_pwm_mode(0));
    tmc_axis_command(Trinamic_ModeToggle, X_AXIS, 0);
    CHECK(tmc_drivers[0]->get_en_pwm_mode(0) && !tmc_drivers[1]->get_en_pwm_mode(1));
    tmc_axis_command(Trinamic_ModeToggle, X_AXIS, 0);
    CHECK(!tmc_drivers[0]->get_en_pwm_mode(0));
    return 0;
}
