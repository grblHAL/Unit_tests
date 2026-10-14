#include "support/rtcp_host.h"

int main(void)
{
    prepare_rtcp();
    const float expected[] = {1, 2, 3, 4, 5, 6, .25f};
    setting_details_t *owner = NULL;
    for(unsigned i = 0; i < 7; i++) {
        char value[16]; snprintf(value, sizeof(value), "%.3f", expected[i]);
        CHECK(settings_store_setting(Setting_Kinematics0 + i, value) == Status_OK);
    }
    for(unsigned i = 0; i < 7; i++) {
        const setting_detail_t *detail = setting_get_details(Setting_Kinematics0 + i, &owner);
        CHECK(detail && owner && owner->load);
        *(float *)detail->value = -99;
    }
    owner->load();
    for(unsigned i = 0; i < 7; i++)
        NEAR(setting_get_float_value(setting_get_details(Setting_Kinematics0 + i, NULL), 0), expected[i]);
    return EXIT_SUCCESS;
}
