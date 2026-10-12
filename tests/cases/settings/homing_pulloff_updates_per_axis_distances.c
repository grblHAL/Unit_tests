#include "support/settings_host.h"
#include "machine_limits.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(store_setting(Setting_HomingPulloff, "2.5") == Status_OK);
    NEAR(settings.homing.pulloff, 2.5f);
    coord_data_t *pulloff = limits_homing_pulloff(NULL);
    for(unsigned axis = 0; axis < N_AXIS; axis++) NEAR(pulloff->values[axis], 2.5f);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
