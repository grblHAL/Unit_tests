#include "support/tool_change_host.h"
int main(void)
{
    prepare_tool_change();
    char fixture[] = "2", automatic[] = "3";
    CHECK(settings_store_setting(Setting_ToolChangeMode, fixture) == Status_InvalidStatement);
    CHECK(settings.tool_change.mode == ToolChange_Manual);
    CHECK(hal.tool.change != NULL && grbl.on_toolchange_ack != NULL);
    CHECK(settings_store_setting(Setting_ToolChangeMode, automatic) == Status_InvalidStatement);
    CHECK(settings.tool_change.mode == ToolChange_Manual);
    CHECK(hal.tool.change != NULL && grbl.on_toolchange_ack != NULL);
    char ignore[] = "4", manual[] = "1";
    CHECK(settings_store_setting(Setting_ToolChangeMode, ignore) == Status_OK);
    CHECK(settings.tool_change.mode == ToolChange_Ignore && hal.tool.change == NULL);
    CHECK(settings_store_setting(Setting_ToolChangeMode, manual) == Status_OK);
    CHECK(settings.tool_change.mode == ToolChange_Manual && hal.tool.change != NULL);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
