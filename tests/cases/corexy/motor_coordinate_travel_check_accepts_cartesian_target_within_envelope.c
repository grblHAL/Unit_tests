#include "support/corexy_limits_host.h"

int main(void)
{
    prepare_corexy_limits();
    work_envelope_t envelope = {.min.values = {-20, -20, -20}, .max.values = {0, 0, 0}};
    float target[N_AXIS] = {-13, -7, -2};
    CHECK(grbl.check_travel_limits(target, (axes_signals_t){.mask = AXES_BITMASK},
                                  false, &envelope) == true);
    NEAR(target[X_AXIS], -13);
    NEAR(target[Y_AXIS], -7);
    NEAR(target[Z_AXIS], -2);
    return EXIT_SUCCESS;
}
