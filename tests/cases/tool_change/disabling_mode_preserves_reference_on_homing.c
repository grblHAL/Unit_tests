#include "support/tool_change_host.h"
#include "check.h"

int main(void)
{
    prepare_tool_change();
    settings.tool_change.mode = ToolChange_Disabled;
    tc_init();
    sys.tlo_reference_set.mask = Z_AXIS_BIT;
    grbl.on_homing_completed((axes_signals_t){.mask = Z_AXIS_BIT}, true);
    CHECK(sys.tlo_reference_set.mask == Z_AXIS_BIT);
    CHECK(homing_calls == 1);
    CHECK(hal.tool.change == NULL && grbl.on_toolchange_ack == NULL);
    return EXIT_SUCCESS;
}
