#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(store_setting(Setting_ArcTolerance, "0.002") == Status_OK);
    NEAR(settings.arc_tolerance, .002f);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
