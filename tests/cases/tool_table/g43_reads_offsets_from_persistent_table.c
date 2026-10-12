#include "support/settings_initialized_host.h"
#include "nvs.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2);
    gc_init(false);
    tool_data_t tool = {.tool_id = 2, .offset.values = {1, 2, 3}};
    CHECK(grbl.tool_table.set_tool(&tool));
    char block[] = "G43H2";
    CHECK(gc_execute_block(block) == Status_OK);
    for(unsigned axis = 0; axis < 3; axis++)
        NEAR(gc_state.modal.tool_length_offset[axis], (float)(axis + 1));
    return EXIT_SUCCESS;
}
