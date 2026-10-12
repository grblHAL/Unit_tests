#include "support/delta_api_host.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    CHECK(delta_store(Setting_Kinematics0, "0.5") == Status_OK);
    const setting_detail_t *setting = setting_get_details(Setting_Kinematics0, NULL);
    NEAR(*(float *)setting->value, 0.5f);
    *(float *)setting->value = 9;
    delta_details()->load();
    NEAR(*(float *)setting->value, 0.5f);
    return EXIT_SUCCESS;
}
