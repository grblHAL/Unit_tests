#include "support/settings_host.h"
#include "state_machine.h"
#include "nvs.h"
int main(void)
{
    prepare_settings_store();
    state_set(STATE_IDLE);
    settings.axis[X_AXIS].jerk = 216000;
    settings.axis[Y_AXIS].jerk = 432000;
    CHECK(settings_override_jerk(X_AXIS, 2));
    CHECK(settings_override_jerk(Y_AXIS, 4));
    settings_write_global();
    settings_t stored;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&stored, NVS_ADDR_GLOBAL, sizeof(stored), true));
    NEAR(stored.axis[X_AXIS].jerk, 216000); NEAR(stored.axis[Y_AXIS].jerk, 432000);
    NEAR(settings.axis[X_AXIS].jerk, 216000); NEAR(settings.axis[Y_AXIS].jerk, 432000);
    return EXIT_SUCCESS;
}
