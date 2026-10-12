#include "support/engine_host.h"
#include "report.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    CHECK(system_n_axis() == N_AXIS);
    CHECK(system_axis_mask() == AXES_BITMASK);
    CHECK(system_claim_axis() == 0);
    CHECK(system_n_axis() == N_AXIS);
    return EXIT_SUCCESS;
}
