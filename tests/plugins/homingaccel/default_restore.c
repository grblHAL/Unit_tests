#include "homing_host.h"
int main(void)
{
    ha_start(true);
    CHECK(saves == 1);
    for (unsigned i = 0; i < N_AXIS; i++)
        NEAR(ha_get(i), (i + 1) * 10.0f);
    return 0;
}
