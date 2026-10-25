#include "offset_host.h"
int main(void)
{
    offset_prepare();
    offset_values(2, 3);
    offset_option(true);
    offset_accept = false;
    CHECK(spindle_select(1));
    CHECK(offset_moves == 1 && offset_syncs == 1);
    CHECK(!offset_planner_syncs && !offset_wco);
    NEAR(gc_state.g92_offset.coord.x, 0);
    NEAR(gc_state.g92_offset.coord.y, 0);
    CHECK(sys.position[0] == 800 && sys.position[1] == 1600);
    return 0;
}
