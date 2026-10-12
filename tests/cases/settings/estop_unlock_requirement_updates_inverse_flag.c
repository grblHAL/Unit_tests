#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    hal.signals_cap.e_stop = true;
    CHECK(store_setting(Setting_UnlockAfterEStop, "0") == Status_OK);
    CHECK(settings.flags.no_unlock_after_estop);
    CHECK(store_setting(Setting_UnlockAfterEStop, "1") == Status_OK);
    CHECK(!settings.flags.no_unlock_after_estop);
    CHECK(change_callbacks == 2);
    return EXIT_SUCCESS;
}
