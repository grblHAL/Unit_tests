#include "support/ganging_settings_host.h"

int main(void)
{
    prepare_ganging();
    const setting_detail_t *detail = ganged_resolution_definition();
    CHECK(((setting_set_float_ptr)detail->value)(detail->id, 82) == Status_SettingValueOutOfRange);
    NEAR(settings.axis[3].steps_per_mm, 80);
    NEAR(setting_get_float_value(detail, 0), 80);
    return EXIT_SUCCESS;
}
