#include "support/linearization_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_linearization_settings();
    CHECK(store_setting(Setting_LinearSpindlePiece1, "1000,1.25,-500") == Status_OK);
    NEAR(settings.pwm_spindle.pwm_piece[0].rpm, 1000);
    NEAR(settings.pwm_spindle.pwm_piece[0].start, 1.25f);
    NEAR(settings.pwm_spindle.pwm_piece[0].end, -500);
    CHECK(change_callbacks == 1);
    const setting_detail_t *detail = setting_get_details(Setting_LinearSpindlePiece1, NULL);
    CHECK(detail != NULL);
    CHECK(strcmp(setting_get_value(detail, 0), "1000,1.25,-500") == 0);
    return EXIT_SUCCESS;
}
