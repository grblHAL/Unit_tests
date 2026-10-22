#include "support/secondary_spindle_host.h"

static const char *linear_units(setting_id_t id, uint_fast8_t axis)
{
    (void)id; (void)axis;
    return "step/mm";
}
static unsigned visits;
static bool inspect_units(const setting_detail_t *setting, uint_fast16_t offset, void *data)
{
    CHECK(data == &visits && offset == visits);
    CHECK(strcmp(setting->unit, offset == A_AXIS ? "step/rev" : "step/mm") == 0);
    visits++;
    return true;
}
int main(void)
{
    prepare_spindle_motor();
    grbl.on_set_axis_setting_unit = linear_units;
    CHECK(st2_motor_bind_spindle(A_AXIS, &settings.axis[A_AXIS]));
    const setting_detail_t *setting = setting_get_details(Setting_AxisStepsPerMM, NULL);
    CHECK(setting);
    CHECK(settings_iterator(setting, inspect_units, &visits));
    CHECK(visits == system_n_axis());
    CHECK(strcmp(setting_get_description((setting_id_t)(Setting_AxisStepsPerMM + A_AXIS)),
                 "Stepper resolution in steps per revolution.") == 0);
    return EXIT_SUCCESS;
}
