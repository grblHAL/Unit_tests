#include "support/boot_host.h"
#include "check.h"
static unsigned door_events;
static void abort_open_door(sys_state_t state) { if(state == STATE_SAFETY_DOOR) { CHECK(boot_reads == 0); door_events++; protocol_enqueue_realtime_command(CMD_EXIT); boot_on_realtime = NULL; } }
int main(void)
{
    boot_control_signals.safety_door_ajar = true;
    boot_on_realtime = abort_open_door;
    boot_startup_program = "G20";
    boot_program = "";
    CHECK(grbl_enter() == 0);
    CHECK(door_events == 1 && !gc_state.modal.units_imperial);
    CHECK(strstr(engine_output, "Check Door") != NULL);
    return EXIT_SUCCESS;
}
