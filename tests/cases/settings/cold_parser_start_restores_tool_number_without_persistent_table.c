#include "support/settings_initialized_host.h"

int main(void)
{
    prepare_initialized_settings(2);
    CHECK(grbl.tool_table.n_tools == 0);
    settings.flags.tool_persistent = true;
    settings.tool_id = 7;
    sys.cold_start = true;
    gc_init(false);
    CHECK(gc_state.tool->tool_id == 7);
    NEAR(gc_state.tool->radius, 0);
    for(unsigned i = 0; i < N_AXIS; i++) NEAR(gc_state.tool->offset.values[i], 0);
    return EXIT_SUCCESS;
}
