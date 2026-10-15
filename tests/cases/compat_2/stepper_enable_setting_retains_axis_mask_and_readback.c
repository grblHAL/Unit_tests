#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    const setting_detail_t *detail = setting_get_details(Setting_InvertStepperEnable, NULL);
    CHECK(detail && detail->datatype == Format_AxisMask);
    CHECK(store_setting(Setting_InvertStepperEnable, "5") == Status_OK);
    CHECK(settings.steppers.enable_invert.mask == 5);
    CHECK(setting_get_int_value(detail, 0) == 5);
    return EXIT_SUCCESS;
}
