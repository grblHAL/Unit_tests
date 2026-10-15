#include "support/energized_motor_settings_host.h"
int main(void)
{
    prepare_energized_motor_settings();
    CHECK(store_setting(Setting_SteppersEnergize, "5") == Status_OK);
    motor_enable_calls = change_callbacks = 0;
    CHECK(store_setting(Setting_SteppersEnergize, "8") == Status_SettingValueOutOfRange);
    CHECK(settings.steppers.energize.mask == 5 && requested_motor_mask.mask == 5);
    CHECK(motor_enable_calls == 0 && change_callbacks == 0);
    return EXIT_SUCCESS;
}
