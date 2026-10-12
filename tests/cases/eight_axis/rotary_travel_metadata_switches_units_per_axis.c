#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2);
    CHECK(store_setting(Settings_RotaryAxes, "1") == Status_OK);
    const setting_detail_t *rotary = setting_get_details((setting_id_t)(Setting_AxisMaxTravel + 3), NULL);
    CHECK(rotary != NULL && strcmp(rotary->unit, "deg") == 0);
    const setting_detail_t *linear = setting_get_details(Setting_AxisMaxTravel, NULL);
    CHECK(linear != NULL && strcmp(linear->unit, "mm") == 0);
    rotary = setting_get_details((setting_id_t)(Setting_AxisMaxTravel + 3), NULL);
    CHECK(rotary != NULL && strcmp(rotary->unit, "deg") == 0);
    return EXIT_SUCCESS;
}
