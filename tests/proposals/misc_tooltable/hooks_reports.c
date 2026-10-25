#include "table_host.h"
int main(void)
{
    start_table();
    tool_data_t tool = *grbl.tool_table.get_tool(1)->data;
    hal.tool.select(&tool, true);
    hal.tool.select(&tool, false);
    grbl.on_tool_changed(&tool);
    CHECK(selections == 2 && changes == 1);
    grbl.on_report_options(true);
    CHECK(options == 1 && reports == 0);
    grbl.on_report_options(false);
    CHECK(options == 2 && reports == 1);
    return 0;
}
