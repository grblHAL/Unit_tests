#include "support/ganging_host.h"

int main(void)
{
    prepare_ganging();
    char value[] = "80.5";
    CHECK(settings_store_setting((setting_id_t)(Setting_AxisStepsPerMM + 3), value) == Status_OK);
    NEAR(settings.axis[3].steps_per_mm, 80.5f);
    const setting_detail_t *detail = setting_get_details((setting_id_t)(Setting_AxisStepsPerMM + 3), NULL);
    CHECK(detail != NULL);
    NEAR(setting_get_float_value(detail, Setting_AxisStepsPerMM + 3 - detail->id), 80.5f);
    return EXIT_SUCCESS;
}
