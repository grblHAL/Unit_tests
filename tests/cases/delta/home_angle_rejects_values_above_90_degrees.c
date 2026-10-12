#include "support/delta_api_host.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    CHECK(delta_store(Setting_Kinematics6, "91") == Status_SettingValueOutOfRange);
    NEAR(*(float *)setting_get_details(Setting_Kinematics6, NULL)->value, 0.0f);
    return EXIT_SUCCESS;
}
