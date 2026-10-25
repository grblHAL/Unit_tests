#include "table_host.h"
#include <string.h>
int main(void)
{
    start_table();
    fail_read = true;
    CHECK(grbl.tool_table.reload() == Status_FileReadError);
    CHECK(grbl.tool_table.get_tool(1)->data && grbl.tool_table.n_tools == 3);
    fail_read = false;
    fail_write = true;
    char before[sizeof(table_text)];
    strcpy(before, table_text);
    tool_data_t tool = *grbl.tool_table.get_tool(1)->data;
    tool.radius = 4;
    CHECK(!grbl.tool_table.set_tool(&tool, true) && strcmp(before, table_text) == 0);
    fail_write = false;
    CHECK(grbl.tool_table.set_tool(&tool, true));
    CHECK(grbl.tool_table.reload() == Status_OK);
    NEAR(grbl.tool_table.get_tool(1)->data->radius, 4);
    CHECK(opens == closes);
    return 0;
}
