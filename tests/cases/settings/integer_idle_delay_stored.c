#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(store_setting(Setting_StepperIdleLockTime, "1234") == Status_OK);
    CHECK(settings.steppers.idle_lock_time == 1234);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
