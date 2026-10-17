#include "support/tool_wco_observer_host.h"
int main(void)
{
    prepare_tool_wco_observer();
    on_wco_saved_ptr wrapped = grbl.on_wco_saved;
    tc_init();
    tc_init();
    CHECK(grbl.on_wco_saved == wrapped);
    tool_wco_block("G10L2P2X3");
    CHECK(tool_wco_events == 1 && tool_wco_id == CoordinateSystem_G55);
    NEAR(tool_wco_data.coord.x, 3);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
