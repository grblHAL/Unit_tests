#include "homing_host.h"
int main(void)
{
    ha_start(true);
    ha_rate(3);
    ha_complete(3, false);
    CHECK(calls[0] == 2 && calls[1] == 2);
    NEAR(acceleration[0], 0);
    NEAR(acceleration[1], 0);
    ha_complete(3, false);
    CHECK(calls[0] == 2 && calls[1] == 2 && complete_calls == 2);
    return 0;
}
