#include "support/boot_spindle_setup_host.h"
#include "check.h"

int main(void)
{
    boot_spindle_reference = 20;
    boot_during_init = register_primary_during_init;
    boot_during_setup = register_setup_spindles;
    boot_program = "$SPINDLESH\n";
    CHECK(grbl_enter() == 0);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(sys.driver_started && sys.alarm == Alarm_None);
    CHECK(settings.spindle.ref_id == 20);
    CHECK(spindle_get(0)->id == 1);
    CHECK(setup_spindle_configurations[1] == 1);
    CHECK(strstr(engine_output, "[SPINDLE:1|0|1|DR|secondary|1000.0,12000.0]") != NULL);
    return EXIT_SUCCESS;
}
