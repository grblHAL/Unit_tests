#include "support/probe_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_probe_settings(); hal.driver_cap.toolsetter=true; CHECK(store_setting(Setting_ProbePullUpDisable,"3")==Status_OK);
    hal.driver_cap.toolsetter=false; const setting_detail_t *detail=setting_get_details(Setting_ProbePullUpDisable,NULL); CHECK(detail!=NULL);
    CHECK(setting_get_int_value(detail,0)==1); CHECK(settings.probe.disable_toolsetter_pullup);
    return EXIT_SUCCESS;
}
