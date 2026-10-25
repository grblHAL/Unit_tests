#include "select_host.h"
#include <string.h>
int main(void)
{
    select_prepare();
    CHECK(select_binding(1, 2) == Status_OK && select_tool_start(1, 10) == Status_OK);
    select_settings->save();
    tool_data_t tool = {.tool_id = 10};
    grbl.on_tool_selected(&tool);
    CHECK(spindle_get_default() == 1 && select_previous_tools == 1);
    tool.tool_id = 5;
    grbl.on_tool_selected(&tool);
    CHECK(spindle_get_default() == 0 && select_previous_tools == 2);
    return 0;
}
