#include "support/settings_validation_host.h"

int main(void)
{
    prepare_settings_store();
    float original = settings.junction_deviation;
    char valid[] = "0.01", invalid[] = "-1";
    CHECK(setting_validate(Setting_JunctionDeviation, 0.01f, valid) == Status_OK);
    CHECK(setting_validate(Setting_JunctionDeviation, -1, invalid) != Status_OK);
    NEAR(settings.junction_deviation, original);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
