#include "support/boot_host.h"
static unsigned plugin_calls;
static status_code_t plugin_command(char *line)
{
    CHECK(strcmp(line, "[fixture:MiXeD value]") == 0);
    CHECK(state_get() == STATE_IDLE);
    plugin_calls++;
    hal.stream.write("[PLUGIN:accepted]" ASCII_EOL);
    return Status_OK;
}
static void install_plugin_command(void) { grbl.on_user_command = plugin_command; }
int main(void)
{
    boot_during_init = install_plugin_command;
    boot_program = "[fixture:MiXeD value]\nG20\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(plugin_calls == 1 && gc_state.modal.units_imperial);
    CHECK(strstr(engine_output, "[PLUGIN:accepted]") != NULL);
    CHECK(strstr(engine_output, "[GC:G0 G54 G17 G20") != NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
