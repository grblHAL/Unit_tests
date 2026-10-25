#include "offset_host.h"
int main(void)
{
    offset_prepare();
    CHECK(spindle_select(1) && spindle_select(0));
    CHECK(!offset_moves && !offset_syncs && !offset_wco && offset_previous == 3);
    return 0;
}
