#include "table_host.h"
int main(void)
{
    start_table();
    CHECK(grbl.tool_table.clear());
    tool_table_entry_t *tool = grbl.tool_table.get_tool(1);
    CHECK(tool->data);
    NEAR(tool->data->radius, 0);
    NEAR(tool->data->offset.z, 0);
    CHECK(grbl.tool_table.reload() == Status_OK);
    tool = grbl.tool_table.get_tool(1);
    CHECK(tool->data);
    NEAR(tool->data->radius, 3);
    NEAR(tool->data->offset.z, 3);
    return 0;
}
