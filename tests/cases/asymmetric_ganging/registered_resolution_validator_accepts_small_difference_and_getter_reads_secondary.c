#include "support/ganging_settings_host.h"

int main(void)
{
    prepare_ganging();
    const setting_detail_t *detail = ganged_resolution_definition();
    CHECK(((setting_set_float_ptr)detail->value)(detail->id, 80.5f) == Status_OK);
    NEAR(setting_get_float_value(detail, 0), 80.5f);
    NEAR(settings.axis[Y_AXIS].steps_per_mm, 80);
    CHECK(((setting_set_float_ptr)detail->value)(detail->id, 79.5f) == Status_OK);
    NEAR(setting_get_float_value(detail, 0), 79.5f);
    return EXIT_SUCCESS;
}
