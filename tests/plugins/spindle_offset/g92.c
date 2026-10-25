#include "offset_host.h"
int main(void)
{
    offset_prepare();
    offset_values(2, -3);
    offset_option(true);
    CHECK(offset_saves == 1 && spindle_select(1));
    NEAR(gc_state.g92_offset.coord.x, 2);
    NEAR(gc_state.g92_offset.coord.y, -3);
    CHECK(offset_wco == 1 && spindle_select(0));
    NEAR(gc_state.g92_offset.coord.x, 0);
    NEAR(gc_state.g92_offset.coord.y, 0);
    CHECK(offset_wco == 2);
    return 0;
}
