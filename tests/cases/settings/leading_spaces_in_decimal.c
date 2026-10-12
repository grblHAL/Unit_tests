#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(store_setting(Setting_JunctionDeviation, "   0.025") == Status_OK);
    NEAR(settings.junction_deviation, .025f);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
