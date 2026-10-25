#include "pulloff_host.h"
int main(void)
{
    load_pulloff();
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    CHECK(chained_changes == 1 && saves == 1);
    set_pulloff(1, 3);
    settings.homing.pulloff = 4;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){.spindle = On});
    CHECK(chained_changes == 2 && last_flags.spindle && saves == 2);
    NEAR(get_pulloff(0), 12);
    NEAR(get_pulloff(1), 3);
    for (unsigned i = 2; i < N_AXIS; i++)
        NEAR(get_pulloff(i), 4);
    unsigned before = updates;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    CHECK(chained_changes == 3 && saves == 2 && updates == before);
    details->load();
    NEAR(requested.values[0], 12);
    NEAR(requested.values[1], 3);
    for (unsigned i = 2; i < N_AXIS; i++)
        NEAR(requested.values[i], 4);
    return 0;
}
