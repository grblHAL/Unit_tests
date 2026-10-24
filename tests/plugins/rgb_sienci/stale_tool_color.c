#include "rgb_host.h"
int main(void)
{
    rgb_start();
    tool_data_t tool = {0};
    bus_busy = true;
    grbl.on_tool_selected(&tool);
    rgb_run_next();
    CHECK(last_delay == 110);
    now += 1;
    grbl.on_tool_changed(&tool);
    rgb_run_next();
    bus_busy = false;
    rgb_run_next();
    rgb_expect(0, 255, 255, 255);
    return 0;
}
