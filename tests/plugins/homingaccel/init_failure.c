#include "homing_host.h"
int main(void)
{
    ha_prepare(true);
    alloc_ok = false;
    homing_accel_init();
    CHECK(!registered_settings);
    ha_rate(1);
    CHECK(rate_calls == 1 && calls[0] == 0);
    return 0;
}
