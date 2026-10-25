#include "pulloff_host.h"
int main(void)
{
    load_pulloff();
    for (unsigned i = 0; i < N_AXIS; i++)
        set_pulloff(i, 4.5f + i);
    details->save();
    CHECK(saves == 2);
    for (unsigned i = 0; i < N_AXIS; i++)
        set_pulloff(i, 9.0f + i);
    details->load();
    CHECK(saves == 2);
    for (unsigned i = 0; i < N_AXIS; i++)
    {
        NEAR(get_pulloff(i), 4.5f + i);
        NEAR(requested.values[i], 4.5f + i);
    }
    return 0;
}
