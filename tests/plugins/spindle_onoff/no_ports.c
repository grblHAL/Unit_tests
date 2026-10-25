#include "onoff_host.h"
int main(void)
{
    on_prepare(TEST_DIRECTION ? 1 : 0);
    CHECK(!on_settings && on_warnings == 1 && !spindle_get(0) && !on_writes);
    return 0;
}
