#include "support/energized_motor_settings_host.h"
int main(void)
{
    prepare_energized_motor_settings();
    CHECK(store_setting(Setting_SteppersEnergize, "5") == Status_OK);
    CHECK(store_setting(Setting_SteppersEnergize, "0") == Status_OK);
    CHECK(settings.steppers.energize.mask == 0 && requested_motor_mask.mask == 0);
    CHECK(motor_enable_calls == 2 && change_callbacks == 2);
    return EXIT_SUCCESS;
}
