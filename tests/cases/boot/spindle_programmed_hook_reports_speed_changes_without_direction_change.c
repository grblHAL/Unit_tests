#include "support/boot_spindle_setup_host.h"
static unsigned programmed_calls;
static void observe_programmed_speed(spindle_ptrs_t *spindle, spindle_state_t state,
                                     float rpm, spindle_rpm_mode_t mode)
{
    const float expected[] = {5000, 7000, 7000};
    CHECK(programmed_calls < 3 && spindle == spindle_get(0));
    CHECK(mode == SpindleSpeedMode_RPM && !state.ccw);
    CHECK(state.on == (programmed_calls < 2));
    NEAR(rpm, expected[programmed_calls]);
    programmed_calls++;
}
static void install_speed_hook(void)
{
    register_primary_during_init();
    grbl.on_spindle_programmed = observe_programmed_speed;
}
int main(void)
{
    boot_spindle_reference = 10;
    boot_during_init = install_speed_hook;
    boot_program = "M3S5000\nM3S7000\nM5\n";
    CHECK(grbl_enter() == 0);
    CHECK(programmed_calls == 3 && !setup_spindle_states[0].on);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
