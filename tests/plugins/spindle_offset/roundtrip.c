#include "offset_host.h"
int main(void)
{
    offset_prepare();
    offset_values(2, -3);
    CHECK(spindle_select(1));
    CHECK(offset_moves == 1 && offset_syncs == 2 && offset_planner_syncs == 1);
    NEAR(offset_target[0], 12);
    NEAR(offset_target[1], 17);
    NEAR(offset_target[2], 30);
    CHECK(spindle_select(0));
    CHECK(offset_moves == 2 && offset_syncs == 4 && offset_planner_syncs == 2);
    NEAR(offset_target[0], 10);
    NEAR(offset_target[1], 20);
    NEAR(gc_state.position[0], 10);
    CHECK(!offset_wco && offset_previous == 3);
    return 0;
}
