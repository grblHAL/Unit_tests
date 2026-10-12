#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.arc_tolerance = 0.1f;
    settings_restore((settings_restore_t){ .defaults = true });
    NEAR(settings.arc_tolerance, DEFAULT_ARC_TOLERANCE);
    settings_t stored;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&stored, NVS_ADDR_GLOBAL, sizeof(stored), true));
    NEAR(stored.arc_tolerance, DEFAULT_ARC_TOLERANCE);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
