#include "pulloff_host.h"
int main(void)
{
    load_pulloff();
    for (unsigned i = 0; i < N_AXIS; i++)
        set_pulloff(i, 20 + i);
    settings.homing.pulloff = 5;
    details->restore();
    CHECK(saves == 2);
    NEAR(get_pulloff(0), 12);
    for (unsigned i = 1; i < N_AXIS; i++)
        NEAR(get_pulloff(i), 5);
    set_pulloff(0, 99);
    details->load();
    NEAR(get_pulloff(0), 12);
    NEAR(requested.values[0], 12);
    CHECK(saves == 2);
    return 0;
}
