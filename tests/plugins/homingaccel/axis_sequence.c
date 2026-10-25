#include "homing_host.h"
int main(void)
{
    ha_start(true);
    ha_set(0, 3);
    ha_set(1, 7);
    ha_rate(1);
    NEAR(acceleration[0], 3);
    CHECK(calls[1] == 0);
    ha_rate(2);
    NEAR(acceleration[0], 0);
    NEAR(acceleration[1], 7);
    CHECK(calls[0] == 2 && rate_calls == 2);
    ha_complete(2, true);
    NEAR(acceleration[1], 0);
    CHECK(complete_calls == 1);
    return 0;
}
