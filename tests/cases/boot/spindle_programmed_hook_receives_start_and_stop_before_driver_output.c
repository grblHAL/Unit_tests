#include "support/boot_spindle_setup_host.h"
static unsigned programmed_calls;
static void observe_programmed_spindle(spindle_ptrs_t *spindle, spindle_state_t state,
                                       float rpm, spindle_rpm_mode_t mode)
{
    CHECK(spindle == spindle_get(0) && programmed_calls < 2);
    CHECK(mode == SpindleSpeedMode_RPM);
    NEAR(rpm, 5000);
    if(programmed_calls == 0) {
        CHECK(state.on && !state.ccw);
        CHECK(!setup_spindle_states[0].on);
    } else {
        CHECK(!state.on);
        CHECK(setup_spindle_states[0].on);
    }
    programmed_calls++;
}
static void install_programmed_hook(void)
{
    register_primary_during_init();
    grbl.on_spindle_programmed = observe_programmed_spindle;
}
int main(void)
{
    boot_spindle_reference = 10;
    boot_during_init = install_programmed_hook;
    boot_program = "M3S5000\nM5\n";
    CHECK(grbl_enter() == 0);
    CHECK(programmed_calls == 2 && !setup_spindle_states[0].on);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
