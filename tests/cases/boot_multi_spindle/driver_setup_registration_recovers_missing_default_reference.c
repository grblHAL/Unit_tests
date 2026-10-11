#include "support/boot_spindle_setup_host.h"
#include "check.h"
static void register_and_select_primary(void)
{
    register_primary_during_init();
    CHECK(spindle_select(0));
}
int main(void)
{
    boot_spindle_reference = 77;
    boot_during_init = register_and_select_primary;
    boot_during_setup = register_setup_spindles;
    boot_program = "$SPINDLESH\n";
    CHECK(grbl_enter() == 0);
    CHECK(sys.driver_started && sys.alarm == Alarm_None);
    CHECK(settings.spindle.ref_id == 10);
    CHECK(spindle_get(0)->id == 0);
    CHECK(setup_spindle_configurations[0] == 1);
    CHECK(strstr(engine_output, "[SPINDLE:0|0|1|DR|primary|1000.0,12000.0]") != NULL);
    return EXIT_SUCCESS;
}
