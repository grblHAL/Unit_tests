#include "support/cutter_parser_host.h"
int main(void)
{
    prepare_cutter_parser();
    CHECK(cutter_block("G10L1P2X4Q9I30J12R0.5") == Status_OK);
    CHECK(cutter_block("G10L1P2R0.75") == Status_OK);
    tool_data_t *tool = grbl.tool_table.get_tool(2)->data;
    CHECK(tool && tool->orientation == (tool_orientation_t)9);
    NEAR(tool->front_angle, 30);
    NEAR(tool->back_angle, 12);
    NEAR(tool->radius, .75f);
    NEAR(tool->offset.values[X_AXIS], 4);
    NEAR(tool->offset.values[Y_AXIS], 2);
    NEAR(tool->offset.values[Z_AXIS], 3);
    return EXIT_SUCCESS;
}
