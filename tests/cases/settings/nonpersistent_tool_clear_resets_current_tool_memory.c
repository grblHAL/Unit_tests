#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2);
    CHECK(grbl.tool_table.n_tools == 0);
    tool_data_t *tool = grbl.tool_table.get_tool(3)->data;
    CHECK(tool != NULL);
    tool->radius = 4;
    tool->offset.values[X_AXIS] = 8;
    CHECK(grbl.tool_table.clear());
    CHECK(tool->tool_id == 0);
    NEAR(tool->radius, 0.0f);
    NEAR(tool->offset.values[X_AXIS], 0.0f);
    return EXIT_SUCCESS;
}
