#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.arc_tolerance = .002f;
    CHECK(store_setting(Setting_ArcTolerance, "-1") == Status_NegativeValue);
    NEAR(settings.arc_tolerance, .002f);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
