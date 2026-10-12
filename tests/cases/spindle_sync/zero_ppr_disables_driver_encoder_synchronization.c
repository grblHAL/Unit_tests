#include "support/spindle_sync_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_sync_motion(); settings.spindle.ppr=0;
    grbl.on_settings_changed(&settings,(settings_changed_flags_t){0}); CHECK(!hal.driver_cap.spindle_sync);
    return EXIT_SUCCESS;
}
