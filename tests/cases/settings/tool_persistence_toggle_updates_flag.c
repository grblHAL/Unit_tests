#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(store_setting(Setting_EnableToolPersistence, "1") == Status_OK);
    CHECK(settings.flags.tool_persistent);
    CHECK(store_setting(Setting_EnableToolPersistence, "0") == Status_OK);
    CHECK(!settings.flags.tool_persistent);
    CHECK(change_callbacks == 2);
    return EXIT_SUCCESS;
}
