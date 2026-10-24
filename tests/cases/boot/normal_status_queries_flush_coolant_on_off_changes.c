#include "support/boot_host.h"

int main(void)
{
    boot_program = "$10=64\nM8\n\x80$G\nM9\n\x80$G\n\n";
    CHECK(grbl_enter() == 0);
    CHECK(settings.status_report.overrides && boot_coolant_seen_on);
    CHECK(boot_coolant_state.mask == 0 && gc_state.modal.coolant.mask == 0);
    const char *on = strstr(engine_output, "|A:F");
    CHECK(on != NULL && strstr(engine_output, "|Ov:100,100,100") != NULL);
    const char *off = strstr(on, "|A:>");
    CHECK(off != NULL && strstr(off, "|A:F") == NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(state_get() == STATE_IDLE && sys.alarm == Alarm_None);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    return EXIT_SUCCESS;
}
