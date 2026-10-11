#include "support/multi_spindle_host.h"
#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle();
    grbl.on_settings_changed = changed_settings;
    hal.driver_cap.spindle_encoder = false;
    CHECK(store_setting(Setting_EncoderSpindle, "1") == Status_SettingDisabled);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
