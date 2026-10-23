#include "support/boot_spindle_setup_host.h"

static bool spindle_sleep_seen, spindle_seen_on;
static unsigned idle_clock_advances;
static void service_spindle_sleep(sys_state_t state)
{
    if(state == STATE_SLEEP) {
        CHECK(spindle_seen_on && !setup_spindle_states[0].on);
        CHECK(boot_coolant_state.mask == 0 && boot_enabled_axes.mask == 0);
        spindle_sleep_seen = true;
        CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
        boot_on_realtime = NULL;
    } else if(state == STATE_IDLE && boot_reads == strlen(boot_program) &&
              settings.flags.sleep_enable && setup_spindle_states[0].on) {
        CHECK(boot_coolant_state.mask == 0);
        CHECK(++idle_clock_advances < 8);
        spindle_seen_on = true;
        engine_ticks += (uint32_t)(SLEEP_DURATION * 60000.0f) + 51;
    }
}

int main(void)
{
    boot_spindle_reference = 10;
    boot_during_init = register_primary_during_init;
    boot_idle_lock_time = 255;
    boot_observe_fault_loop = true;
    boot_on_realtime = service_spindle_sleep;
    boot_program = "$62=1\nM3S5000\n";
    CHECK(grbl_enter() == 0);
    CHECK(spindle_sleep_seen && idle_clock_advances > 0);
    CHECK(!setup_spindle_states[0].on && !boot_coolant_seen_on);
    CHECK(strstr(engine_output, "Sleeping") != NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
