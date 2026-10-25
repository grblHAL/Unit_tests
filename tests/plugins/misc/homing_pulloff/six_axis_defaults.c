#include "pulloff_host.h"
int main(void)
{
    load_pulloff();
    const float expected[] = {12, 3, 4, 5, 6, 7};
    CHECK(N_AXIS == 6 && saves == 1);
    for (unsigned i = 0; i < N_AXIS; i++)
    {
        NEAR(get_pulloff(i), expected[i]);
        NEAR(requested.values[i], expected[i]);
    }
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    settings.homing.pulloff = 10;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    CHECK(chained_changes == 2);
    for (unsigned i = 0; i < N_AXIS; i++)
        NEAR(get_pulloff(i), expected[i]);
    return 0;
}
