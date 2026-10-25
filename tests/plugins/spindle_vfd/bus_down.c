#include "vfd_host.h"
int main(void)
{
    vfd_bus_up = false;
    vfd_prepare(true);
    CHECK(vfd_settings);
    vfd_settings->load();
    CHECK(!spindle_select(0) && vfd_requests == 0 && spindle_get_default() == -2);
    vfd_bus_up = true;
    CHECK(spindle_select(0));
    return 0;
}
