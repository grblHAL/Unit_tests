#include "support/settings_initialized_host.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2);
    for(tool_id_t id = 1; id <= 4; id++) {
        tool_data_t tool = {.tool_id = id, .radius = 3, .offset.values = {1, 2, 3}};
        CHECK(grbl.tool_table.set_tool(&tool));
    }
    CHECK(grbl.tool_table.clear());
    for(tool_id_t id = 1; id <= 4; id++) {
        tool_data_t *tool = grbl.tool_table.get_tool(id)->data;
        CHECK(tool && tool->tool_id == id);
        NEAR(tool->radius, 0.0f);
        for(unsigned axis = 0; axis < N_AXIS; axis++) NEAR(tool->offset.values[axis], 0.0f);
    }
    return EXIT_SUCCESS;
}
