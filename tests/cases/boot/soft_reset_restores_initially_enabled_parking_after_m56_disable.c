#include "support/boot_host.h"
static bool initially_enabled, disabled_before_reset;
static void configure_parking(void)
{
    settings.parking.flags.enabled = true;
    settings.parking.flags.enable_override_control = true;
    settings.parking.flags.deactivate_upon_init = false;
    settings_write_global();
}
static void observe_parking(void)
{
    if(boot_reads == 0) {
        CHECK(!sys.override.control.parking_disable);
        CHECK(!gc_state.modal.override_ctrl.parking_disable);
        initially_enabled = true;
    }
    if(boot_program[boot_reads] == CMD_RESET) {
        CHECK(sys.override.control.parking_disable);
        CHECK(gc_state.modal.override_ctrl.parking_disable);
        disabled_before_reset = true;
    }
}
int main(void)
{
    boot_during_init = configure_parking;
    boot_before_read = observe_parking;
    boot_program = "M56P0\n\x18$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(initially_enabled && disabled_before_reset);
    CHECK(!sys.override.control.parking_disable);
    CHECK(!gc_state.modal.override_ctrl.parking_disable);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
