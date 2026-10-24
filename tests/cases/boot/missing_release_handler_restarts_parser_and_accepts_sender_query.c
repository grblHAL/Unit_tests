#include "support/boot_host.h"

static bool second_program;
static void omit_release_handler(void) { hal.driver_release = NULL; }
static void observe_persistent_controller(void)
{
    const char *first = strstr(engine_output, "GrblHAL ");
    CHECK(first != NULL);
    const char *second = strstr(first + strlen("GrblHAL "), "GrblHAL ");
    if(second == NULL) return;
    CHECK(hal.driver_release == NULL && boot_release_calls == 0);
    CHECK(boot_setup_calls == 1 && settings.status_report.mask == 64);
    if(!second_program) {
        CHECK(!gc_state.modal.distance_incremental);
        NEAR(gc_state.feed_rate, 0);
        CHECK(strstr(engine_output, " G91 ") != NULL);
        boot_program = "$G\n";
        boot_reads = 0;
        second_program = true;
    } else if(boot_reads == strlen(boot_program)) {
        CHECK(strstr(second, "[GC:") != NULL && strstr(second, " G90 ") != NULL);
        CHECK(strstr(engine_output, "error:") == NULL);
        CHECK(state_get() == STATE_IDLE && sys.alarm == Alarm_None);
        CHECK(plan_get_current_block() == NULL);
        /* With no release handler the controller intentionally stays alive.
           End the host observer after the second sender query succeeds. */
        exit(EXIT_SUCCESS);
    }
}
int main(void)
{
    boot_during_init = omit_release_handler;
    boot_before_read = observe_persistent_controller;
    boot_program = "$10=64\nG91F200\n$G\n";
    (void)grbl_enter();
    CHECK(false);
    return EXIT_FAILURE;
}
