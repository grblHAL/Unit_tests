#include "overdrive_host.h"
int main(void)
{
    ovd_prepare();
    settings.pwm_spindle.flags.enable_rpm_controlled = Off;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){.spindle = On});
    CHECK(grbl.user_mcode.check(Laser_Overdrive) == UserMCode_Unsupported);
    settings.pwm_spindle.flags.enable_rpm_controlled = On;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){.spindle = On});
    CHECK(grbl.user_mcode.check(Laser_Overdrive) == UserMCode_Normal);
    settings.pwm_spindle.flags.laser_mode_disable = On;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){.spindle = On});
    CHECK(grbl.user_mcode.check(Laser_Overdrive) == UserMCode_Unsupported && ovd_settings == 3);
    return 0;
}
