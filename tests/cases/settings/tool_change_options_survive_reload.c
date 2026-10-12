#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2.0f);
    CHECK(store_setting(Setting_ToolChangeOptions, "6") == Status_OK);
    CHECK(settings.flags.no_restore_position_after_M6);
    CHECK(settings.flags.tool_change_at_g30);
    CHECK(settings.flags.tool_change_fast_pulloff);
    settings.flags.no_restore_position_after_M6 = false;
    settings.flags.tool_change_at_g30 = false;
    settings.flags.tool_change_fast_pulloff = false;
    settings_init();
    CHECK(settings.flags.no_restore_position_after_M6);
    CHECK(settings.flags.tool_change_at_g30);
    CHECK(settings.flags.tool_change_fast_pulloff);
    CHECK(strcmp(setting_get_value(setting_get_details(Setting_ToolChangeOptions, NULL), 0), "6") == 0);
    CHECK(store_setting(Setting_ToolChangeOptions, "1") == Status_OK);
    CHECK(!settings.flags.no_restore_position_after_M6);
    CHECK(!settings.flags.tool_change_at_g30);
    CHECK(!settings.flags.tool_change_fast_pulloff);
    return EXIT_SUCCESS;
}
