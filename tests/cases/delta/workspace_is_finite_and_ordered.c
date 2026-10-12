#include "support/delta_host.h"
#include "check.h"

int main(void)
{
    prepare_delta();
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(isfinite(sys.work_envelope.min.values[axis]));
        CHECK(isfinite(sys.work_envelope.max.values[axis]));
        CHECK(sys.work_envelope.min.values[axis] < sys.work_envelope.max.values[axis]);
    }
    CHECK(sys.work_envelope.max.z < 0);
    return EXIT_SUCCESS;
}
