#include "select_host.h"
#include <string.h>
int main(void)
{
    select_prepare();
    CHECK(select_binding(1, 2) == Status_OK && select_tool_start(1, 10) == Status_OK);
    select_settings->save();
    CHECK(select_tool_start(1, 0) == Status_OK);
    select_settings->save();
    CHECK(spindle_select(0));
    tool_data_t tool = {.tool_id = 20};
    grbl.on_tool_selected(&tool);
    CHECK(spindle_get_default() == 0 && select_previous_tools == 1);
    return 0;
}
