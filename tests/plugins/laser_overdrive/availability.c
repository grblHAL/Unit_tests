#include "overdrive_host.h"
int main(void)
{
    ovd_prepare();
    CHECK(grbl.user_mcode.check(Laser_Overdrive) == UserMCode_Normal);
    CHECK(spindle_select(1));
    CHECK(grbl.user_mcode.check(Laser_Overdrive) == UserMCode_Unsupported);
    CHECK(spindle_select(0));
    CHECK(grbl.user_mcode.check(Laser_Overdrive) == UserMCode_Normal && ovd_selected == 3);
    return 0;
}
