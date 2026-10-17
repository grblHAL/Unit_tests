#include "support/boot_host.h"
static unsigned demarcations;
static bool events[2];
static void settings_batch_event(bool start)
{
    CHECK(demarcations < 2);
    CHECK(state_get() == STATE_ALARM);
    events[demarcations++] = start;
}
static void install_batch_observer(void) { grbl.on_file_demarcate = settings_batch_event; }
int main(void)
{
    boot_force_alarm = true;
    boot_during_init = install_batch_observer;
    boot_program = "%\n$11=0.02\nG91\n%\n";
    CHECK(grbl_enter() == 0);
    CHECK(demarcations == 2 && events[0] && !events[1]);
    NEAR(settings.junction_deviation, .02f);
    CHECK(state_get() == STATE_ALARM);
    CHECK(!gc_state.file_run && !gc_state.modal.distance_incremental);
    CHECK(strstr(engine_output, "error:9") != NULL);
    return EXIT_SUCCESS;
}
