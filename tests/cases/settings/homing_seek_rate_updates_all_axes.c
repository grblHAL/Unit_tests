#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(store_setting(Setting_HomingSeekRate, "250") == Status_OK);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        NEAR(settings.axis[axis].homing_seek_rate, 250);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
