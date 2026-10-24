#include "rgb_host.h"
int main(void)
{
    rgb_prepare();
    grbl.on_state_change = NULL;
    grbl.on_tool_selected = NULL;
    grbl.on_tool_changed = NULL;
    grbl.on_program_completed = NULL;
    grbl.user_mcode = (user_mcode_ptrs_t){0};
    status_light_init();
    rgb_run_next();
    rgb_state(STATE_CYCLE);
    rgb_expect(0, 0, 255, 0);
    parser_block_t block = {.user_mcode = (user_mcode_t)999};
    CHECK(grbl.user_mcode.check(block.user_mcode) == UserMCode_Unsupported);
    CHECK(grbl.user_mcode.validate(&block) == Status_Unhandled);
    grbl.user_mcode.execute(STATE_IDLE, &block);
    tool_data_t tool = {0};
    grbl.on_tool_selected(&tool);
    rgb_run_next();
    rgb_expect(0, 255, 0, 255);
    grbl.on_tool_changed(&tool);
    rgb_run_next();
    rgb_expect(0, 0, 255, 0);
    grbl.on_program_completed((program_flow_t)0, false);
    for (unsigned i = 0; i < 10; i++)
        rgb_run_next();
    CHECK(!pending && warnings == 0 && chains == 0);
    rgb_expect(0, 0, 255, 0);
    return 0;
}
