#include "overdrive_host.h"
int main(void)
{
    ovd_initial_select = false;
    ovd_prepare();
    CHECK(grbl.user_mcode.check(Laser_Overdrive) == UserMCode_Unsupported);
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){.spindle = On});
    hal.driver_reset();
    grbl.on_program_completed(ProgramFlow_CompletedM30, false);
    CHECK(ovd_settings == 1 && ovd_resets == 1 && ovd_completions == 1);
    CHECK(spindle_select(0) && grbl.user_mcode.check(Laser_Overdrive) == UserMCode_Normal);
    return 0;
}
