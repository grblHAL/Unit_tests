#include "table_host.h"
int main(void)
{
    file_exists = false;
    start_table();
    CHECK(grbl.tool_table.n_tools == 0 && opens == 0 && closes == 0);
    CHECK(grbl.tool_table.reload() == Status_FileReadError);
    CHECK(grbl.tool_table.get_tool(1)->data == NULL);
    return 0;
}
