#include "support/settings_initialized_host.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2);
    gc_init(false);
    char block[] = "G10L1P2X1.25Y2.5Z3.75R4.5";
    CHECK(gc_execute_block(block) == Status_OK);
    tool_data_t *tool = grbl.tool_table.get_tool(2)->data;
    CHECK(tool && tool->tool_id == 2);
    NEAR(tool->offset.values[0], 1.25f);
    NEAR(tool->offset.values[1], 2.5f);
    NEAR(tool->offset.values[2], 3.75f);
    NEAR(tool->radius, 4.5f);
    return EXIT_SUCCESS;
}
