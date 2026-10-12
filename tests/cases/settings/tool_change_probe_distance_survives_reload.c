#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2.0f);
    CHECK(store_setting(Setting_ToolChangeProbingDistance, "27.5") == Status_OK);
    settings.tool_change.probing_distance = 1;
    settings_init();
    NEAR(settings.tool_change.probing_distance, 27.5f);
    CHECK(strcmp(setting_get_value(setting_get_details(Setting_ToolChangeProbingDistance, NULL), 0), "27.5") == 0);
    return EXIT_SUCCESS;
}
