#include "support/square_host.h"
static unsigned disable_calls;
static axes_signals_t driver_disabled_axes;
static squaring_mode_t driver_mode;
static void driver_disable(axes_signals_t axes, squaring_mode_t mode)
{
    disable_calls++;
    driver_disabled_axes = axes;
    driver_mode = mode;
}
int main(void)
{
    ganging_driver_disable = driver_disable;
    prepare_square();
    hal.stepper.disable_motors((axes_signals_t){.mask = Y_AXIS_BIT}, SquaringMode_B);
    CHECK(disable_calls == 1 && driver_disabled_axes.mask == Y_AXIS_BIT);
    CHECK(driver_mode == SquaringMode_B);
    stepper_t first = {.step_out = {.mask = AXES_BITMASK}};
    hal.stepper.pulse_start(&first);
    CHECK(motor_mask == (AXES_BITMASK & ~(1u << (N_AXIS - 1))));
    hal.stepper.disable_motors((axes_signals_t){0}, SquaringMode_Both);
    CHECK(disable_calls == 2 && driver_disabled_axes.mask == 0);
    CHECK(driver_mode == SquaringMode_Both);
    stepper_t second = {.step_out = {.mask = AXES_BITMASK}};
    hal.stepper.pulse_start(&second);
    CHECK(pulse_calls == 2 && motor_mask == AXES_BITMASK);
    return EXIT_SUCCESS;
}
