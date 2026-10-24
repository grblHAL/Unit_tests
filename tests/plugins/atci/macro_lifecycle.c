#include "atci_host.h"
int main(void)
{
    atci_start();
    atci_flags(5);
    tool_data_t tool = {0};
    CHECK(!atci_check(20, 20));
    grbl.on_tool_selected(&tool);
    CHECK(atci_check(20, 20));
    atci_report();
    CHECK(strstr(output, "|ATCI:T|previous"));
    gpio[7] = false;
    grbl.on_tool_changed(&tool);
    CHECK(!atci_check(20, 20));
    gpio[7] = true;
    grbl.on_tool_selected(&tool);
    grbl.on_tool_changed(&tool);
    CHECK(atci_check(20, 20));
    return 0;
}
