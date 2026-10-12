#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2);
    CHECK(store_setting(Settings_RotaryAxes, "1") == Status_OK);
    const setting_detail_t *rotary = setting_get_details((setting_id_t)(Setting_AxisAcceleration + 3), NULL);
    CHECK(rotary != NULL && strcmp(rotary->unit, "deg/sec^2") == 0);
    const setting_detail_t *linear = setting_get_details(Setting_AxisAcceleration, NULL);
    CHECK(linear != NULL && strcmp(linear->unit, "mm/sec^2") == 0);
    rotary = setting_get_details((setting_id_t)(Setting_AxisAcceleration + 3), NULL);
    CHECK(rotary != NULL && strcmp(rotary->unit, "deg/sec^2") == 0);
    return EXIT_SUCCESS;
}
