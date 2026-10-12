#include "support/square_host.h"
#include "check.h"

int main(void)
{
    prepare_square();
    stepper_t stepper = {.step_out = {.bits = 15}};
    hal.stepper.pulse_start(&stepper);
    CHECK(pulse_calls == 1);
    CHECK(motor_mask == 15);
    return EXIT_SUCCESS;
}
