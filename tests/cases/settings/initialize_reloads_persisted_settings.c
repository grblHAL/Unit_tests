#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2.0f);
    CHECK(store_setting(Setting_ArcTolerance, "0.005") == Status_OK);
    settings.arc_tolerance = 0.9f;
    change_callbacks = 0;
    settings_init();
    NEAR(settings.arc_tolerance, 0.005f);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
