#include "support/spindle_sync_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_sync_motion(); settings_changed_flags_t changed={.spindle=true};
    grbl.on_settings_changed(&settings,changed); CHECK(sync_settings_calls==1); CHECK(sync_last_changed.spindle);
    grbl.on_settings_changed(&settings,(settings_changed_flags_t){0}); CHECK(sync_settings_calls==2); CHECK(!sync_last_changed.spindle);
    return EXIT_SUCCESS;
}
