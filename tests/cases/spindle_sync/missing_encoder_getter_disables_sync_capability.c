#include "support/spindle_sync_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_sync_motion(); hal.spindle_data.get=NULL;
    grbl.on_settings_changed(&settings,(settings_changed_flags_t){0}); CHECK(!hal.driver_cap.spindle_sync); CHECK(sync_settings_calls==1);
    return EXIT_SUCCESS;
}
