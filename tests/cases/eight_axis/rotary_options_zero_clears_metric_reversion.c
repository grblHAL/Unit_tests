#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.flags.rotary_fix_enable = settings.flags.revert_metric_conversion = true;
    CHECK(store_setting(Setting_RotaryOptions, "0") == Status_OK);
    CHECK(!settings.flags.rotary_fix_enable && !settings.flags.revert_metric_conversion);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
