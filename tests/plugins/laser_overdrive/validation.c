#include "overdrive_host.h"
int main(void)
{
    ovd_prepare();
    CHECK(ovd_command(-1, false) == Status_GcodeValueOutOfRange);
    CHECK(ovd_command(NAN, false) == Status_GcodeValueOutOfRange);
    CHECK(ovd_command(12.5f, true) == Status_OK);
    NEAR(spindle_get(0)->context.pwm->off_overdrive_pct, 12.5f);
    parser_block_t block = {.user_mcode = Laser_Overdrive};
    CHECK(grbl.user_mcode.validate(&block) == Status_GcodeValueWordMissing);
    return 0;
}
