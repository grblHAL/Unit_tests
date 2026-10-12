#include "support/boot_host.h"
#include "check.h"
static unsigned door_events;
static void close_without_resume(sys_state_t state) { if(state == STATE_SAFETY_DOOR) { CHECK(boot_reads == 0); if(++door_events == 1) boot_control_signals.safety_door_ajar = false; else { CHECK(!boot_control_signals.safety_door_ajar); protocol_enqueue_realtime_command(CMD_EXIT); boot_on_realtime = NULL; } } }
int main(void)
{
    boot_control_signals.safety_door_ajar = true;
    boot_on_realtime = close_without_resume;
    boot_startup_program = "G20";
    boot_program = "";
    CHECK(grbl_enter() == 0);
    CHECK(door_events == 2 && !gc_state.modal.units_imperial);
    CHECK(boot_reads == 0);
    return EXIT_SUCCESS;
}
