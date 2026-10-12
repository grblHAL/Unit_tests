#include "support/engine_host.h"
#include "report.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    gc_state.modal.plane_select = PlaneSelect_XY;
    sys.tlo_reference_set.mask = Z_AXIS_BIT;
    system_clear_tlo_reference((axes_signals_t){.mask = X_AXIS_BIT});
    CHECK(sys.tlo_reference_set.mask == Z_AXIS_BIT);
    CHECK(!(hal.stream.report.flags.value & Report_TLOReference));
    return EXIT_SUCCESS;
}
