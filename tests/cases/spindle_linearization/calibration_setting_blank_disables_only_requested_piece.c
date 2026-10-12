#include "support/linearization_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_linearization_settings();
    settings.pwm_spindle.pwm_piece[0] = (pwm_piece_t){.rpm = 1000, .start = 1, .end = 2};
    settings.pwm_spindle.pwm_piece[1] = (pwm_piece_t){.rpm = 5000, .start = 0.5f, .end = -2500};
    CHECK(store_setting(Setting_LinearSpindlePiece1, "") == Status_OK);
    CHECK(isnan(settings.pwm_spindle.pwm_piece[0].rpm));
    NEAR(settings.pwm_spindle.pwm_piece[0].start, 0);
    NEAR(settings.pwm_spindle.pwm_piece[0].end, 0);
    NEAR(settings.pwm_spindle.pwm_piece[1].rpm, 5000);
    const setting_detail_t *detail = setting_get_details(Setting_LinearSpindlePiece1, NULL);
    CHECK(detail != NULL && strcmp(setting_get_value(detail, 0), "") == 0);
    return EXIT_SUCCESS;
}
