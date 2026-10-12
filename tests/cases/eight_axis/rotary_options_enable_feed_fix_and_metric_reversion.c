#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(store_setting(Setting_RotaryOptions, "3") == Status_OK);
    CHECK(settings.flags.rotary_fix_enable && settings.flags.revert_metric_conversion);
    const setting_detail_t *detail = setting_get_details(Setting_RotaryOptions, NULL);
    CHECK(detail != NULL && setting_get_int_value(detail, 0) == 3);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
