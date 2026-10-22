#include "support/cutter_parser_host.h"
int main(void)
{
    prepare_cutter_parser();
    CHECK(cutter_block("G10L1P2X4Q3I30J12R0.5") == Status_OK);
    tool_data_t *tool = grbl.tool_table.get_tool(2)->data;
    CHECK(tool && tool->tool_id == 2 && tool->orientation == ToolPos3_315);
    NEAR(tool->front_angle, 30);
    NEAR(tool->back_angle, 12);
    NEAR(tool->radius, .5f);
    NEAR(tool->offset.values[X_AXIS], 4);
    NEAR(tool->offset.values[Y_AXIS], 2);
    NEAR(tool->offset.values[Z_AXIS], 3);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
