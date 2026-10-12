#include "support/boot_host.h"
#include "check.h"
static unsigned door_events;
static void close_and_resume(sys_state_t state) { if(state == STATE_SAFETY_DOOR) { CHECK(boot_reads == 0); boot_control_signals.safety_door_ajar = false; system_set_exec_state_flag(EXEC_CYCLE_START); door_events++; boot_on_realtime = NULL; } }
int main(void)
{
    boot_control_signals.safety_door_ajar = true;
    boot_on_realtime = close_and_resume;
    boot_program = "G20\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(door_events == 1 && gc_state.modal.units_imperial);
    CHECK(strstr(engine_output, "Check Door") != NULL);
    CHECK(strstr(engine_output, "[GC:G0 G54 G17 G20 G90") != NULL);
    return EXIT_SUCCESS;
}
