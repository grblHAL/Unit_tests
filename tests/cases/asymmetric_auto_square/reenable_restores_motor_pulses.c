#include "support/square_host.h"
#include "check.h"

int main(void)
{
    prepare_square();
    hal.stepper.disable_motors((axes_signals_t){.bits = 1u << Y_AXIS}, SquaringMode_B);
    hal.stepper.disable_motors((axes_signals_t){0}, SquaringMode_Both);
    stepper_t stepper = {.step_out = {.bits = 15}};
    hal.stepper.pulse_start(&stepper);
    CHECK(motor_mask == 15);
    return EXIT_SUCCESS;
}
