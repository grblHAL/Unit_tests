#include "support/tool_change_host.h"
#include "check.h"

int main(void)
{
    prepare_tool_change();
    sys.tlo_reference_set.mask = Z_AXIS_BIT;
    grbl.on_homing_completed((axes_signals_t){.mask = X_AXIS_BIT}, true);
    CHECK(sys.tlo_reference_set.mask == Z_AXIS_BIT);
    CHECK(homing_calls == 1 && homing_success);
    CHECK(homing_axes.mask == X_AXIS_BIT);
    return EXIT_SUCCESS;
}
