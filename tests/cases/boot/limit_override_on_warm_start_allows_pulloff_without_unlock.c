#include "support/boot_host.h"
static stream_write_ptr output_all;
static unsigned welcomes;
static void press_override_after_warm_welcome(const char *text)
{
    output_all(text);
    if(strstr(text, "GrblHAL") && ++welcomes == 2) {
        CHECK(sys.alarm == Alarm_LimitsEngaged);
        CHECK(boot_limit_signals.min.x);
        boot_control_signals.limits_override = true;
    }
}
static void install_override_input(settings_t *current)
{
    CHECK(current == &settings);
    hal.signals_cap.limits_override = true;
    output_all = hal.stream.write_all;
    hal.stream.write_all = press_override_after_warm_welcome;
}
int main(void)
{
    boot_check_limits = true;
    boot_limit_signals.min.x = true;
    boot_during_setup = install_override_input;
    boot_program = "$G\n\x18" "G91\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(welcomes == 2 && boot_control_signals.limits_override);
    CHECK(boot_limit_signals.min.x && settings.limits.flags.hard_enabled);
    CHECK(gc_state.modal.distance_incremental && state_get() == STATE_IDLE);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(strstr(engine_output, "[GC:G0 G54 G17 G21 G91") != NULL);
    return EXIT_SUCCESS;
}
