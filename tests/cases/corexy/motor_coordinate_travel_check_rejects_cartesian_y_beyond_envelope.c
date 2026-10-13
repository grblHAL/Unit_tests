#include "support/corexy_limits_host.h"

int main(void)
{
    prepare_corexy_limits();
    work_envelope_t envelope = {.min.values = {-20, -20, -20}, .max.values = {0, 0, 0}};
    float target[N_AXIS] = {-21, 21, -2};
    CHECK(grbl.check_travel_limits(target, (axes_signals_t){.mask = AXES_BITMASK},
                                  false, &envelope) == false);
    NEAR(target[X_AXIS], -21);
    NEAR(target[Y_AXIS], 21);
    NEAR(target[Z_AXIS], -2);
    return EXIT_SUCCESS;
}
