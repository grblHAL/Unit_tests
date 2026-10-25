#include "table_host.h"
#include <string.h>
int main(void)
{
    start_table();
    CHECK(grbl.tool_table.n_tools == 3);
    tool_table_entry_t *tool = grbl.tool_table.get_tool(1);
    CHECK(tool->data && tool->pocket == 1 && strcmp(tool->name, "mill%rough") == 0);
    NEAR(tool->data->offset.x, 1);
    NEAR(tool->data->offset.y, -2);
    NEAR(tool->data->offset.z, 3);
    NEAR(tool->data->radius, 3);
    tool = grbl.tool_table.get_tool(2);
    CHECK(tool->data && tool->pocket == 7);
    NEAR(tool->data->offset.z, -4);
    NEAR(tool->data->radius, 1.5f);
    CHECK(grbl.tool_table.get_tool_by_idx(1)->data->tool_id == 1);
    CHECK(grbl.tool_table.get_tool_by_idx(2)->data->tool_id == 2);
    CHECK(grbl.tool_table.get_tool(999)->data == NULL &&
          grbl.tool_table.get_tool_by_idx(3)->data == NULL);
    return 0;
}
