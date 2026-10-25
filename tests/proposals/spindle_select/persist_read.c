#include "select_host.h"
int main(void)
{
    select_load_image = true;
    select_prepare();
    CHECK(spindle_select_get_binding(1) == 1);
    tool_data_t tool = {.tool_id = 10};
    grbl.on_tool_selected(&tool);
    CHECK(spindle_get_default() == 1 && select_previous_tools == 1);
    CHECK(select_command(false, 1, true) == Status_OK);
    return 0;
}
