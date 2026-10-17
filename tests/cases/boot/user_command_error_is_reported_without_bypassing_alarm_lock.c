#include "support/boot_host.h"
static unsigned plugin_calls;
static status_code_t reject_plugin_command(char *line)
{
    CHECK(strcmp(line, "[fixture:reject]") == 0);
    CHECK(state_get() == STATE_ALARM);
    plugin_calls++;
    return Status_InvalidStatement;
}
static void install_plugin_command(void) { grbl.on_user_command = reject_plugin_command; }
int main(void)
{
    boot_force_alarm = true;
    boot_during_init = install_plugin_command;
    boot_program = "[fixture:reject]\nG91\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(plugin_calls == 1 && state_get() == STATE_ALARM);
    CHECK(!gc_state.modal.distance_incremental);
    CHECK(strstr(engine_output, "error:3") != NULL);
    CHECK(strstr(engine_output, "error:9") != NULL);
    CHECK(strstr(engine_output, "[GC:G0 G54 G17 G21 G90") != NULL);
    return EXIT_SUCCESS;
}
