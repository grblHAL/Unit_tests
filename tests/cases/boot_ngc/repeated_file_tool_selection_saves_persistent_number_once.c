#include "support/boot_host.h"
#include "fs_embedded.h"

#define MACRO_TEXT "O<toolrepeat>SUB\nM61Q7\nM61Q7\nO<toolrepeat>ENDSUB\n"
static const embedded_file_t macro = {.name = "toolrepeat.macro",
    .size = sizeof(MACRO_TEXT) - 1, .data = MACRO_TEXT};
static const embedded_file_t *macros[] = {&macro, NULL};
static memcpy_to_nvs_ptr native_write;
static on_tool_changed_ptr native_tool_changed;
static unsigned global_writes, tool_notifications;
static bool observers_installed, saved_seen;
static bool observe_write(uint32_t dest, uint8_t *source, uint32_t size, bool checksum)
{
    if(dest == NVS_ADDR_GLOBAL) global_writes++;
    return native_write(dest, source, size, checksum);
}
static void observe_tool(tool_data_t *tool)
{
    CHECK(tool->tool_id == 7);
    tool_notifications++;
    native_tool_changed(tool);
}
static void install_observers(void)
{
    if(observers_installed) {
        if(tool_notifications == 2 && hal.stream.file == NULL && !saved_seen) {
            settings_t saved = {0};
            CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&saved, NVS_ADDR_GLOBAL, sizeof(saved), true) == NVS_TransferResult_OK);
            CHECK(saved.tool_id == 7 && saved.flags.tool_persistent);
            saved_seen = true;
        }
        return;
    }
    CHECK(settings.flags.tool_persistent);
    native_write = hal.nvs.memcpy_to_nvs;
    native_tool_changed = grbl.on_tool_changed;
    CHECK(native_write && native_tool_changed);
    hal.nvs.memcpy_to_nvs = observe_write;
    grbl.on_tool_changed = observe_tool;
    observers_installed = true;
}
static void enable_tool_persistence(settings_t *current)
{
    CHECK(current == &settings);
    char enabled[] = "1";
    CHECK(settings_store_setting(Setting_EnableToolPersistence, enabled) == Status_OK);
}
static void mount_macro(void) { fs_embedded_mount(macros); }
int main(void)
{
    boot_during_init = mount_macro;
    boot_during_setup = enable_tool_persistence;
    boot_before_read = install_observers;
    boot_program = "O<toolrepeat>CALL\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(observers_installed && tool_notifications == 2 && global_writes == 1);
    CHECK(gc_state.tool->tool_id == 7 && settings.tool_id == 7);
    CHECK(saved_seen);
    CHECK(hal.stream.file == NULL && sys.alarm == Alarm_None && state_get() == STATE_IDLE);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
