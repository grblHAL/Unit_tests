#include "support/boot_host.h"

static bool initial_alarm_seen, sleep_report_requested, reset_sent, warm_query_sent;
static unsigned sleep_polls, accepted_alarm_polls;

static void service_alarm_sleep(sys_state_t state)
{
    if(state != STATE_SLEEP) {
        if(initial_alarm_seen && !sleep_report_requested && state == STATE_ALARM && strstr(engine_output, "ok" ASCII_EOL) &&
           ++accepted_alarm_polls == 8) {
            fprintf(stderr, "Accepted $SLP remains in alarm after eight foreground polls.\n");
            CHECK(state_get() == STATE_SLEEP);
        }
        return;
    }
    CHECK(initial_alarm_seen && ++sleep_polls < 1000);
    CHECK(boot_enabled_axes.mask == 0 && boot_coolant_state.mask == 0);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(sys.position[axis] == 0);
    if(!sleep_report_requested) {
        CHECK(protocol_enqueue_realtime_command(CMD_STATUS_REPORT));
        sleep_report_requested = true;
    } else if(!reset_sent && sleep_polls >= 4 && strstr(engine_output, "<Sleep|")) {
        CHECK(protocol_enqueue_realtime_command(CMD_RESET));
        reset_sent = true;
    }
}
static void observe_alarm_and_restart(void)
{
    CHECK(strstr(engine_output, "error:") == NULL);
    if(!initial_alarm_seen && boot_reads == 0) {
        CHECK(state_get() == STATE_ALARM && settings.flags.sleep_enable);
        initial_alarm_seen = true;
    }
    if(reset_sent && state_get() == STATE_ALARM && !warm_query_sent) {
        boot_program = "$X\n$G\n";
        boot_reads = 0;
        boot_observe_fault_loop = false;
        warm_query_sent = true;
    }
}

int main(void)
{
    boot_force_alarm = true;
    boot_sleep_enabled = true;
    boot_idle_lock_time = 255;
    boot_observe_fault_loop = true;
    boot_on_realtime = service_alarm_sleep;
    boot_before_read = observe_alarm_and_restart;
    boot_program = "$SLP\n\n\n";
    CHECK(grbl_enter() == 0);
    CHECK(initial_alarm_seen && sleep_report_requested && reset_sent && warm_query_sent);
    CHECK(sleep_polls >= 4 && state_get() == STATE_IDLE);
    CHECK(strstr(engine_output, "<Sleep|") != NULL);
    CHECK(strstr(engine_output, "[GC:G0 G54 G17 G21 G90") != NULL);
    CHECK(boot_enabled_axes.mask == 0 && boot_coolant_state.mask == 0);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
