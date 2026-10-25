#include "offset_host.h"
int main(void)
{
    offset_prepare();
    offset_values(2, 3);
    CHECK(spindle_select(2));
    CHECK(!offset_moves && offset_syncs == 1);
    CHECK(spindle_select(0));
    CHECK(!offset_moves && offset_syncs == 2);
    return 0;
}
