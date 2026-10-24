#include "homing_host.h"
int main(void)
{
    ha_start(true);
    accept_override = false;
    ha_rate(1);
    CHECK(calls[0] == 1);
    ha_complete(1, false);
    CHECK(calls[0] == 1);
    accept_override = true;
    ha_rate(1);
    NEAR(acceleration[0], 10);
    ha_complete(1, true);
    NEAR(acceleration[0], 0);
    return 0;
}
