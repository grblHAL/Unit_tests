#include "support/square_host.h"
#include "check.h"

int main(void)
{
    prepare_square();
    fixture_limits.min.bits = (1u << X_AXIS) | (1u << 3);
    limit_signals_t observed = hal.limits.get_state();
    CHECK(observed.min.bits == fixture_limits.min.bits);
    CHECK(observed.min2.bits == (1u << Y_AXIS));
    return EXIT_SUCCESS;
}
