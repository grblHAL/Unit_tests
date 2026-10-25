#include "homing_host.h"
int main(void)
{
    ha_start(true);
    ha_set(0, 0);
    ha_rate(1);
    CHECK(calls[0] == 0);
    ha_set(0, 5);
    ha_rate(1);
    NEAR(acceleration[0], 5);
    ha_set(0, 0);
    ha_rate(1);
    CHECK(calls[0] == 2);
    NEAR(acceleration[0], 0);
    return 0;
}
