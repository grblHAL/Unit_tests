#include "support/linearization_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_linearization_settings();
    settings.pwm_spindle.pwm_piece[1] = (pwm_piece_t){.rpm = 5000, .start = 0.5f, .end = -2500};
    CHECK(store_setting(Setting_LinearSpindlePiece2, "0") == Status_OK);
    CHECK(isnan(settings.pwm_spindle.pwm_piece[1].rpm));
    NEAR(settings.pwm_spindle.pwm_piece[1].start, 0);
    NEAR(settings.pwm_spindle.pwm_piece[1].end, 0);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
