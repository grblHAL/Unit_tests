#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(store_setting(Setting_ArcTolerance, "0.003") == Status_OK);
    settings_t stored;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&stored, NVS_ADDR_GLOBAL, sizeof(stored), true));
    NEAR(stored.arc_tolerance, .003f);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
