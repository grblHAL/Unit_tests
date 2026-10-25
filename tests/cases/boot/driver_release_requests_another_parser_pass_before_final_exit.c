#include "support/boot_host.h"

static bool another_pass(void)
{
    CHECK(++boot_release_calls <= 2);
    if(boot_release_calls == 1) {
        CHECK(gc_state.modal.distance_incremental);
        NEAR(gc_state.feed_rate, 200);
        CHECK(settings.status_report.mask == 64);
        boot_program = "$G\n";
        boot_reads = 0;
        return true;
    }
    CHECK(!gc_state.modal.distance_incremental);
    NEAR(gc_state.feed_rate, 0);
    return false;
}
static void register_release_handler(void) { hal.driver_release = another_pass; }
int main(void)
{
    boot_during_init = register_release_handler;
    boot_program = "$10=64\nG91F200\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 2);
    CHECK(settings.status_report.mask == 64 && state_get() == STATE_IDLE);
    const char *first = strstr(engine_output, "GrblHAL ");
    CHECK(first != NULL);
    const char *second = strstr(first + strlen("GrblHAL "), "GrblHAL ");
    CHECK(second != NULL && strstr(second + strlen("GrblHAL "), "GrblHAL ") == NULL);
    CHECK(strstr(engine_output, " G91 ") != NULL && strstr(second, " G90 ") != NULL);
    CHECK(strstr(second, "[GC:") != NULL && strstr(engine_output, "error:") == NULL);
    CHECK(sys.alarm == Alarm_None && plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
