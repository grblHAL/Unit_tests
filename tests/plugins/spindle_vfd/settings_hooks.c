#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    settings.spindle.at_speed_tolerance = 10;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){.spindle = On});
    CHECK(vfd_previous_settings == 1 && vfd_motor->get_data(SpindleData_AtSpeed)->at_speed_enabled);
    vfd_motor->update_rpm(vfd_motor, 6000);
    CHECK(vfd_motor->get_data(SpindleData_AtSpeed)->rpm_low_limit == 5400);
    grbl.on_report_options(true);
    grbl.on_report_options(false);
    CHECK(vfd_previous_reports == 2);
    return 0;
}
