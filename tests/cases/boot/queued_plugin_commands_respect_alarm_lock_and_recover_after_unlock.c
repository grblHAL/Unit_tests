#include "support/boot_host.h"
static unsigned plugin_stage;
static void queue_plugin_command(const char *text)
{
    char command[32];
    CHECK(strlen(text) < sizeof(command));
    strcpy(command, text);
    CHECK(protocol_enqueue_gcode(command));
    plugin_stage++;
}
static void service_plugin_commands(void)
{
    switch(plugin_stage) {
        case 0:
            CHECK(state_get() == STATE_ALARM);
            queue_plugin_command("G20G91");
            break;
        case 1:
            if(strstr(engine_output, "error:9")) {
                CHECK(!gc_state.modal.units_imperial && !gc_state.modal.distance_incremental);
                queue_plugin_command("$G");
            }
            break;
        case 2:
            if(strstr(engine_output, "[GC:G0 G54 G17 G21 G90")) {
                CHECK(state_get() == STATE_ALARM);
                queue_plugin_command("$X");
            }
            break;
        case 3:
            if(state_get() == STATE_IDLE) queue_plugin_command("G20G91");
            break;
        case 4:
            if(gc_state.modal.units_imperial && gc_state.modal.distance_incremental) {
                CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
                plugin_stage++;
            }
            break;
    }
}
int main(void)
{
    boot_force_alarm = true;
    boot_program = "";
    boot_observe_fault_loop = true; /* Let the observer finish after the last reply. */
    boot_before_read = service_plugin_commands;
    CHECK(grbl_enter() == 0);
    CHECK(plugin_stage == 5 && boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(gc_state.modal.units_imperial && gc_state.modal.distance_incremental);
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
