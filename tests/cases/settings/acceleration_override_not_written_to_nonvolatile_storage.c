#include "support/settings_host.h"
#include "state_machine.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    state_set(STATE_IDLE);
    settings.axis[X_AXIS].acceleration = 12345;
    CHECK(settings_override_acceleration(X_AXIS, 25));
    settings_write_global();
    settings_t stored;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&stored, NVS_ADDR_GLOBAL, sizeof(stored), true));
    NEAR(stored.axis[X_AXIS].acceleration, 12345);
    NEAR(settings.axis[X_AXIS].acceleration, 12345);
    return EXIT_SUCCESS;
}
