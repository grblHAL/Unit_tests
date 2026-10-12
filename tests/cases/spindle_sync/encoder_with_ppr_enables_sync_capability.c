#include "support/spindle_sync_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_sync_motion(); CHECK(hal.driver_cap.spindle_sync); CHECK(sync_settings_calls==0);
    CHECK(grbl.on_settings_changed==st_spindle_sync_cfg);
    return EXIT_SUCCESS;
}
