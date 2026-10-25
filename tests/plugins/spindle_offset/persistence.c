#include "offset_host.h"
int main(void)
{
    offset_prepare();
    offset_values(4, -5);
    offset_settings->save();
    offset_values(0, 0);
    offset_settings->load();
    CHECK(spindle_select(1));
    NEAR(offset_target[0], 14);
    NEAR(offset_target[1], 15);
    return 0;
}
