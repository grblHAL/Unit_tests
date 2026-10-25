#include "support/boot_host.h"
static bool timed_sleep_seen;
static unsigned idle_clock_advances;
static void service_idle_sleep(sys_state_t state)
{
    if(state == STATE_SLEEP) {
        CHECK(settings.flags.sleep_enable && boot_coolant_seen_on);
        CHECK(boot_coolant_state.mask == 0 && boot_enabled_axes.mask == 0);
        timed_sleep_seen = true;
        CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
        boot_on_realtime = NULL;
    } else if(state == STATE_IDLE && boot_reads == strlen(boot_program) &&
              settings.flags.sleep_enable && boot_coolant_state.flood) {
        CHECK(++idle_clock_advances < 8);
        engine_ticks += (uint32_t)(SLEEP_DURATION * 60000.0f) + 51;
    }
}
int main(void)
{
    boot_idle_lock_time = 255;
    boot_observe_fault_loop = true;
    boot_on_realtime = service_idle_sleep;
    boot_program = "$62=1\nM8\n";
    CHECK(grbl_enter() == 0);
    CHECK(timed_sleep_seen && idle_clock_advances > 0);
    CHECK(settings.flags.sleep_enable && boot_coolant_seen_on);
    CHECK(strstr(engine_output, "Sleeping") != NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
