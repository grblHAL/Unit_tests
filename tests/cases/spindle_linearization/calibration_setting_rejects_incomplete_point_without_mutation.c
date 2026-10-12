#include "support/linearization_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_linearization_settings();
    settings.pwm_spindle.pwm_piece[0] = (pwm_piece_t){.rpm = 1000, .start = 1, .end = 2};
    CHECK(store_setting(Setting_LinearSpindlePiece1, "1000,1") == Status_SettingValueOutOfRange);
    NEAR(settings.pwm_spindle.pwm_piece[0].rpm, 1000);
    NEAR(settings.pwm_spindle.pwm_piece[0].start, 1);
    NEAR(settings.pwm_spindle.pwm_piece[0].end, 2);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
