#include "hal.h"
#include "check.h"
int main(void)
{
    stepper_state_t state = {0};
    stepper_state_t result = xbar_stepper_state_set(&state, X_AXIS, false);
    CHECK(result.details.a.bits == 1 && result.details.b.bits == 0);
    result = xbar_stepper_state_set(&state, Y_AXIS, true);
    CHECK(result.details.a.bits == 1 && result.details.b.bits == 2);
    result = xbar_stepper_state_set(&state, X_AXIS, true);
    CHECK(result.details.a.bits == 1 && result.details.b.bits == 3);
    CHECK(xbar_stepper_state_get(state, X_AXIS, false));
    CHECK(!xbar_stepper_state_get(state, Y_AXIS, false));
    CHECK(xbar_stepper_state_get(state, X_AXIS, true));
    CHECK(xbar_stepper_state_get(state, Y_AXIS, true));
    CHECK(!xbar_stepper_state_get(state, Z_AXIS, true));
    return EXIT_SUCCESS;
}
