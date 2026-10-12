#include "support/ganging_host.h"
#include "check.h"

int main(void)
{
    prepare_ganging();
    CHECK(hal.stepper.get_ganged(false).bits == (1u << Y_AXIS));
    CHECK(hal.stepper.get_ganged(true).bits == 0);
    return EXIT_SUCCESS;
}
