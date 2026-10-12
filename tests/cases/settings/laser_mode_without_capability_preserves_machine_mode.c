#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.mode = Mode_Lathe;
    gc_state.modal.diameter_mode = true;
    CHECK(store_setting(Setting_Mode, "1") == Status_SettingDisabledLaser);
    CHECK(settings.mode == Mode_Lathe);
    CHECK(gc_state.modal.diameter_mode);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
