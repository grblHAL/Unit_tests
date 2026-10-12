#include "support/boot_host.h"
#include "check.h"
static bool sleep_coolant_checked;
static void check_sleep_coolant(sys_state_t state) { if(state == STATE_SLEEP) { CHECK(boot_coolant_seen_on && boot_coolant_state.mask == 0); sleep_coolant_checked = true; protocol_enqueue_realtime_command(CMD_EXIT); boot_on_realtime = NULL; } }
int main(void)
{
    boot_sleep_enabled = true;
    boot_on_realtime = check_sleep_coolant;
    boot_program = "M8\n$SLP\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(sleep_coolant_checked && boot_coolant_seen_on);
    CHECK(strstr(engine_output, "Sleeping") != NULL);
    return EXIT_SUCCESS;
}
