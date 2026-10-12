#include "support/build_report_host.h"
#include "check.h"

int main(void)
{
    prepare_build_report();
    hal.coolant_cap.mist = true;
    settings.parking.flags.enabled = true;
    settings.homing.flags.force_set_origin = true;
    settings.homing.flags.single_axis_commands = true;
    settings.limits.flags.two_switches = true;
    settings.probe.allow_feed_override = true;
    spindle_get(0)->cap.direction = false;
    settings.pwm_spindle.flags.enable_rpm_controlled = true;
    hal.driver_cap.software_debounce = true;
    settings.parking.flags.enable_override_control = true;
    settings.homing.flags.init_lock = false;
    hal.signals_cap.safety_door_ajar = true;
    settings.status_report.sync_on_wco_change = false;
    build_report(true);
    CHECK(strstr(engine_output, "[OPT:NMPZHTAD0SRL+W,") != NULL);
    return EXIT_SUCCESS;
}
