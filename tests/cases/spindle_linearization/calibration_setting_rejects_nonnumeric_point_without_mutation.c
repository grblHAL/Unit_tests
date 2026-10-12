#include "support/linearization_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_linearization_settings();
    CHECK(store_setting(Setting_LinearSpindlePiece1, "invalid") == Status_SettingValueOutOfRange);
    CHECK(isnan(settings.pwm_spindle.pwm_piece[0].rpm));
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
