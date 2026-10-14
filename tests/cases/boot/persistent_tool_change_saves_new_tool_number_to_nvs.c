#include "support/boot_host.h"

static bool checked_persistence;
static void change_tool_during_running_controller(void)
{
    if(checked_persistence) return;
    settings.flags.tool_persistent = true;
    settings.tool_id = 3;
    tool_data_t tool = {.tool_id = 7};
    grbl.on_tool_changed(&tool);
    CHECK(settings.tool_id == 7);
    settings_t saved = {0};
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&saved, NVS_ADDR_GLOBAL, sizeof(saved), true) == NVS_TransferResult_OK);
    CHECK(saved.tool_id == 7 && saved.flags.tool_persistent);
    checked_persistence = true;
}

int main(void)
{
    boot_before_read = change_tool_during_running_controller;
    CHECK(grbl_enter() == 0);
    CHECK(checked_persistence);
    return EXIT_SUCCESS;
}
