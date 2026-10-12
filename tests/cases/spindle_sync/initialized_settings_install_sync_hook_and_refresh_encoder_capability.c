#include "support/spindle_sync_motion_host.h"
#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2);
    CHECK(grbl.on_settings_changed==st_spindle_sync_cfg); CHECK(!hal.driver_cap.spindle_sync);
    hal.f_step_timer=1000000; hal.driver_cap.spindle_encoder=true; hal.spindle_data.get=sync_motion_data;
    CHECK(store_setting(Setting_SpindlePPR,"100")==Status_OK);
    CHECK(settings.spindle.ppr==100); CHECK(hal.driver_cap.spindle_sync); CHECK(change_callbacks==1);
    CHECK(grbl.on_settings_changed==st_spindle_sync_cfg);
    return EXIT_SUCCESS;
}
