#include "homing_host.h"
int main(void)
{
    ha_start(true);
    ha_set(0, 4);
    ha_set(2, 9);
    ha_rate(5);
    NEAR(acceleration[0], 4);
    NEAR(acceleration[2], 9);
    CHECK(calls[1] == 0);
    ha_complete(1, true);
    NEAR(acceleration[0], 0);
    NEAR(acceleration[2], 9);
    ha_complete(4, true);
    NEAR(acceleration[2], 0);
    return 0;
}
