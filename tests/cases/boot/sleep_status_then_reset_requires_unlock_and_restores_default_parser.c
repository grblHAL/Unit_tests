#include "support/boot_host.h"
static unsigned sleep_turns;
static bool sleep_report_requested, sleep_reset_sent, warm_query_sent;
static void observe_sleep_and_request_reset(sys_state_t state)
{
    if(state != STATE_SLEEP) return;
    CHECK(++sleep_turns < 1000);
    CHECK(boot_enabled_axes.mask == 0 && boot_coolant_state.mask == 0);
    if(!sleep_report_requested) {
        CHECK(protocol_enqueue_realtime_command(CMD_STATUS_REPORT));
        sleep_report_requested = true;
    } else if(!sleep_reset_sent && strstr(engine_output, "<Sleep|")) {
        CHECK(protocol_enqueue_realtime_command(CMD_RESET));
        sleep_reset_sent = true;
    }
}
static void send_query_after_sleep_reset(void)
{
    if(sleep_reset_sent && state_get() == STATE_ALARM && !warm_query_sent) {
        boot_program = "$G\n";
        boot_reads = 0;
        warm_query_sent = true;
        boot_observe_fault_loop = false;
    }
}
int main(void)
{
    boot_sleep_enabled = true;
    boot_idle_lock_time = 255;
    /* Keep the simulated sender connected while the controller waits for reset. */
    boot_observe_fault_loop = true;
    boot_on_realtime = observe_sleep_and_request_reset;
    boot_before_read = send_query_after_sleep_reset;
    boot_program = "M8\nG20\n$SLP\n\n\n";
    CHECK(grbl_enter() == 0);
    CHECK(boot_coolant_seen_on && sleep_report_requested && sleep_reset_sent && warm_query_sent);
    CHECK(state_get() == STATE_ALARM && !sys.position_lost);
    CHECK(!gc_state.modal.units_imperial);
    CHECK(strstr(engine_output, "<Sleep|") != NULL);
    CHECK(strstr(engine_output, "[GC:G0 G54 G17 G21 G90") != NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    const char *banner = strstr(engine_output, "GrblHAL 1.1f");
    CHECK(banner && strstr(banner + 1, "GrblHAL 1.1f"));
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    return EXIT_SUCCESS;
}
