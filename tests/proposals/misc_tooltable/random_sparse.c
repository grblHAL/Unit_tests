#include "table_host.h"
int main(void)
{
    settings.macro_atc_flags.random_toolchanger = On;
    start_table();
    CHECK(grbl.tool_table.get_tool(1)->data);
    CHECK(grbl.tool_table.get_tool(2)->data != NULL);
    return 0;
}
