#include "support/boot_host.h"

int main(void)
{
    CHECK(grbl_enter() == 0);
    settings.flags.tool_persistent = false;
    settings.tool_id = 3;
    tool_data_t tool = {.tool_id = 7};
    grbl.on_tool_changed(&tool);
    CHECK(settings.tool_id == 3);
    return EXIT_SUCCESS;
}
