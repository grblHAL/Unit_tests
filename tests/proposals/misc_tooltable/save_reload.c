#include "table_host.h"
#include <string.h>
int main(void)
{
    start_table();
    tool_data_t tool = *grbl.tool_table.get_tool(1)->data;
    tool.offset.z = -8.5f;
    tool.radius = 2.25f;
    CHECK(grbl.tool_table.set_tool(&tool, true));
    CHECK(strstr(table_text, "Z-8.500") && strstr(table_text, "D4.500"));
    CHECK(grbl.tool_table.reload() == Status_OK);
    tool_table_entry_t *reloaded = grbl.tool_table.get_tool(1);
    CHECK(reloaded->data);
    NEAR(reloaded->data->offset.z, -8.5f);
    NEAR(reloaded->data->radius, 2.25f);
    CHECK(grbl.tool_table.get_tool(2)->pocket == 7 && opens == closes);
    return 0;
}
