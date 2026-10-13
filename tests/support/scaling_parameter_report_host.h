#pragma once
#include "support/report_host.h"

static inline void check_scaling_parameter_report(void)
{
    float *factors = gc_get_scaling();
    NEAR(factors[X_AXIS], 2); NEAR(factors[Y_AXIS], 3); NEAR(factors[Z_AXIS], 4);
    engine_output[0] = '\0';
    report_ngc_parameters();
    float x, y, z;
    CHECK(sscanf(engine_output, "[G51:%f,%f,%f]", &x, &y, &z) == 3);
    fprintf(stderr, "Scaling factors reported: %g,%g,%g; expected 2,3,4\n", x, y, z);
    NEAR(x, 2); NEAR(y, 3); NEAR(z, 4);
}
