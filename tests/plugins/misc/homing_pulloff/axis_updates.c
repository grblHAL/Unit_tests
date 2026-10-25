#include "pulloff_host.h"
int main(void)
{
    load_pulloff();
    for (unsigned i = 0; i < N_AXIS; i++)
    {
        set_pulloff(i, 0.25f + i);
        NEAR(get_pulloff(i), 0.25f + i);
        NEAR(requested.values[i], 0.25f + i);
    }
    for (unsigned i = 0; i < N_AXIS; i++)
        NEAR(requested.values[i], 0.25f + i);
    CHECK(saves == 1);
    const setting_detail_t *s = details->settings;
    unsigned before = updates;
    CHECK(((setting_set_float_ptr)s->value)(Setting_AxisExtended8, 10) == Status_SettingDisabled);
    CHECK(((setting_get_float_ptr)s->get_value)(Setting_AxisExtended8) == 0);
    CHECK(updates == before && saves == 1);
    return 0;
}
