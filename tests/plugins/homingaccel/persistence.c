#include "homing_host.h"
int main(void)
{
    ha_start(true);
    ha_set(0, 2);
    ha_set(2, 8);
    registered_settings->save();
    ha_set(0, 99);
    registered_settings->load();
    NEAR(ha_get(0), 2);
    NEAR(ha_get(2), 8);
    CHECK(saves == 2);
    return 0;
}
