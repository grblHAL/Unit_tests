#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.mode = Mode_Lathe;
    gc_state.modal.diameter_mode = true;
    CHECK(store_setting(Setting_Mode, "0") == Status_OK);
    CHECK(settings.mode == Mode_Standard);
    CHECK(!gc_state.modal.diameter_mode);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
