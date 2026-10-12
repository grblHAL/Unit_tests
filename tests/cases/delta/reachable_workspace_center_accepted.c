#include "support/delta_host.h"
#include "check.h"

int main(void)
{
    prepare_delta();
    sys.homed.bits = 7;
    coord_data_t target = {.z = (sys.work_envelope.min.z + sys.work_envelope.max.z) / 2};
    CHECK(grbl.check_travel_limits(target.values, (axes_signals_t){.bits = 7}, true, &sys.work_envelope));
    return EXIT_SUCCESS;
}
