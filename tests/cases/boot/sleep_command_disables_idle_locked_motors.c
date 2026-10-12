#include "support/boot_host.h"
#include "check.h"
static bool initial_motors_checked, sleep_motors_checked;
static void check_initial_motors(void) { CHECK(boot_enabled_axes.mask == AXES_BITMASK); initial_motors_checked = true; boot_before_read = NULL; }
static void check_sleep_motors(sys_state_t state) { if(state == STATE_SLEEP) { CHECK(boot_enabled_axes.mask == 0); sleep_motors_checked = true; protocol_enqueue_realtime_command(CMD_EXIT); boot_on_realtime = NULL; } }
int main(void)
{
    boot_sleep_enabled = true;
    boot_idle_lock_time = 255;
    boot_before_read = check_initial_motors;
    boot_on_realtime = check_sleep_motors;
    boot_program = "$SLP\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(initial_motors_checked && sleep_motors_checked);
    CHECK(strstr(engine_output, "Sleeping") != NULL);
    return EXIT_SUCCESS;
}
