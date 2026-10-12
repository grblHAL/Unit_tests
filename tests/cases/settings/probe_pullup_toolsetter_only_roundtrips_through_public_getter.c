#include "support/probe_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_probe_settings(); hal.driver_cap.toolsetter=true;
    CHECK(store_setting(Setting_ProbePullUpDisable,"2")==Status_OK);
    const setting_detail_t *detail=setting_get_details(Setting_ProbePullUpDisable,NULL); CHECK(detail!=NULL);
    CHECK(setting_get_int_value(detail,0)==2); CHECK(change_callbacks==1); CHECK(probe_configure_calls==0);
    return EXIT_SUCCESS;
}
