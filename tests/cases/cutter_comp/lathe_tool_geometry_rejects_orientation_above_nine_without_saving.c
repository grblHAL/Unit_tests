#include "support/cutter_parser_host.h"
int main(void)
{
    prepare_cutter_parser();
    tool_data_t before = *grbl.tool_table.get_tool(2)->data;
    CHECK(cutter_block("G10L1P2X99Q10I30J12R0.5") == Status_GcodeValueOutOfRange);
    CHECK(memcmp(&before, grbl.tool_table.get_tool(2)->data, sizeof(before)) == 0);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
