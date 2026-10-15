#include "support/settings_host.h"
#include "state_machine.h"
#include "nvs.h"
int main(void)
{
    prepare_settings_store();
    state_set(STATE_IDLE);
    settings.axis[X_AXIS].jerk = 216000;
    CHECK(settings_override_jerk(X_AXIS, 4));
    CHECK(store_setting(Setting_ArcTolerance, "0.005") == Status_OK);
    settings_t stored;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&stored, NVS_ADDR_GLOBAL, sizeof(stored), true));
    NEAR(stored.axis[X_AXIS].jerk, 216000);
    NEAR(stored.arc_tolerance, 0.005f);
    NEAR(settings.axis[X_AXIS].jerk, 216000);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}

