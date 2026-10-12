#include "support/ganging_host.h"
#include "check.h"

int main(void)
{
    prepare_ganging();
    fixture_limits.min.bits = 1u << Y_AXIS;
    limit_signals_t observed = hal.limits.get_state();
    CHECK(observed.min.bits == ((1u << Y_AXIS) | (1u << 3)));
    fixture_limits.min.bits = 1u << X_AXIS;
    observed = hal.limits.get_state();
    CHECK(observed.min.bits == (1u << X_AXIS));
    return EXIT_SUCCESS;
}
