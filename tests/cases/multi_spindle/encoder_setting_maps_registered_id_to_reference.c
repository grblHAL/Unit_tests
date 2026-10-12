#include "support/multi_spindle_host.h"
#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle();
    grbl.on_settings_changed = changed_settings;
    hal.driver_cap.spindle_encoder = true;
    CHECK(store_setting(Setting_EncoderSpindle, "2") == Status_OK);
    CHECK(settings.spindle.encoder_spindle == 30);
    CHECK(spindle_get(0)->id == 0);
    const setting_detail_t *setting = setting_get_details(Setting_EncoderSpindle, NULL);
    CHECK(setting != NULL);
    CHECK(setting_get_int_value(setting, 0) == 2);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
