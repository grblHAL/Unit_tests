#include "support/square_host.h"
#include "check.h"

int main(void)
{
    prepare_square();
    hal.stepper.disable_motors((axes_signals_t){.bits = 1u << Y_AXIS}, SquaringMode_B);
    stepper_t stepper = {.step_out = {.bits = 15}};
    hal.stepper.pulse_start(&stepper);
    CHECK(pulse_calls == 1);
    CHECK(motor_mask == (15u & ~(1u << 3)));
    return EXIT_SUCCESS;
}
