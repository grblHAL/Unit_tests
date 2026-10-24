#include "rgb_host.h"
int main(void)
{
    rgb_start();
    tool_data_t tool = {0};
    unsigned before = chains;
    grbl.on_tool_selected(&tool);
    CHECK(last_delay == 100 && chains == before + 1);
    rgb_run_next();
    rgb_expect(0, 255, 0, 255);
    grbl.on_tool_changed(&tool);
    CHECK(last_delay == 100 && chains == before + 2);
    rgb_run_next();
    rgb_expect(0, 255, 255, 255);
    return 0;
}
