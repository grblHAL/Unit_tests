#include "support/cutter_parser_host.h"
int main(void)
{
    prepare_cutter_parser();
    CHECK(cutter_block("G20") == Status_OK);
    CHECK(cutter_block("G10L1P2X1Q0I30J12R0.25") == Status_OK);
    tool_data_t *tool = grbl.tool_table.get_tool(2)->data;
    CHECK(tool && tool->orientation == (tool_orientation_t)0);
    NEAR(tool->offset.values[X_AXIS], 25.4f);
    NEAR(tool->radius, 6.35f);
    NEAR(tool->front_angle, 30);
    NEAR(tool->back_angle, 12);
    NEAR(tool->offset.values[Y_AXIS], 2);
    NEAR(tool->offset.values[Z_AXIS], 3);
    return EXIT_SUCCESS;
}
