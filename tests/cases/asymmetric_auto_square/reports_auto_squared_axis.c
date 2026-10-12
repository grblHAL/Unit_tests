#include "support/square_host.h"
#include "check.h"

int main(void)
{
    prepare_square();
    CHECK(hal.stepper.get_ganged(false).bits == (1u << Y_AXIS));
    CHECK(hal.stepper.get_ganged(true).bits == (1u << Y_AXIS));
    return EXIT_SUCCESS;
}
