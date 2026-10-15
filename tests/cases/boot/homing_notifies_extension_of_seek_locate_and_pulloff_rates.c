#include "support/boot_homing_motion_host.h"
static homing_mode_t observed_modes[4];
static float observed_rates[4];
static unsigned rate_calls;
static void observe_homing_rate(axes_signals_t axes, coord_data_t *rate, homing_mode_t mode)
{
    CHECK(axes.mask == X_AXIS_BIT && rate_calls < 4);
    observed_modes[rate_calls] = mode;
    observed_rates[rate_calls++] = rate->values[X_AXIS];
}
static void install_rate_homing_driver(void)
{
    install_boot_homing_driver();
    grbl.on_homing_rate_set = observe_homing_rate;
}
int main(void)
{
    prepare_boot_homing_motion();
    boot_during_init = install_rate_homing_driver;
    CHECK(grbl_enter() == 0);
    CHECK(rate_calls == 4);
    CHECK(observed_modes[0] == HomingMode_Seek && observed_modes[1] == HomingMode_Pulloff);
    CHECK(observed_modes[2] == HomingMode_Locate && observed_modes[3] == HomingMode_Pulloff);
    NEAR(observed_rates[0], 100);
    NEAR(observed_rates[1], 100);
    NEAR(observed_rates[2], 25);
    NEAR(observed_rates[3], 100);
    CHECK(boot_motor_pulses[X_AXIS] == 110 && boot_motor_position[X_AXIS] == 70);
    CHECK(sys.homed.mask == X_AXIS_BIT);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
