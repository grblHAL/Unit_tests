#include "offset_host.h"
int main(void)
{
    offset_prepare();
    offset_values(2, 3);
    sys.driver_started = Off;
    CHECK(spindle_select(1));
    CHECK(!offset_moves && !offset_syncs);
    return 0;
}
