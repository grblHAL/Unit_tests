#include "support/tool_change_host.h"
#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_tool_change();
    grbl.on_settings_changed = changed_settings;
    tool_select_ptr original_wrapper = hal.tool.select;
    CHECK(store_setting(Setting_ToolChangeMode, "0") == Status_OK);
    CHECK(hal.tool.change == NULL);
    CHECK(store_setting(Setting_ToolChangeMode, "1") == Status_OK);
    CHECK(settings.tool_change.mode == ToolChange_Manual);
    CHECK(hal.tool.change != NULL && grbl.on_toolchange_ack != NULL);
    CHECK(hal.tool.select == original_wrapper);
    CHECK(change_callbacks == 2);
    return EXIT_SUCCESS;
}
