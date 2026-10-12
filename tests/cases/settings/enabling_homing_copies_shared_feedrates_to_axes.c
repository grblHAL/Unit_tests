#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.axis[0].homing_feed_rate = 125;
    settings.axis[0].homing_seek_rate = 700;
    settings.axis[1].homing_feed_rate = 5;
    settings.axis[1].homing_seek_rate = 10;
    CHECK(store_setting(Setting_HomingEnable, "1") == Status_OK);
    CHECK(settings.homing.flags.enabled);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        NEAR(settings.axis[axis].homing_feed_rate, 125);
        NEAR(settings.axis[axis].homing_seek_rate, 700);
    }
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
