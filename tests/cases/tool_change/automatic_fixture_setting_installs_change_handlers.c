#include "support/tool_change_host.h"
#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_tool_change();
    grbl.on_settings_changed = changed_settings;
    CHECK(store_setting(Setting_ToolChangeMode, "3") == Status_OK);
    CHECK(settings.tool_change.mode == ToolChange_SemiAutomatic);
    CHECK(hal.tool.change != NULL && grbl.on_toolchange_ack != NULL);
    settings_t stored;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&stored, NVS_ADDR_GLOBAL, sizeof(stored), true));
    CHECK(stored.tool_change.mode == ToolChange_SemiAutomatic);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
