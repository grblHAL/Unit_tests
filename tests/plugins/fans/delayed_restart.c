#include "fan_host.h"

int main(void)
{
    load_fans();
    *(float *)fan_setting(Setting_Fan0OffDelay)->value = 0.5f;
    fan_set_state(0, true);
    grbl.on_program_completed((program_flow_t)0, false);
    CHECK(outputs[0] && delayed_task && delayed_ms == 30000);
    parser_block_t block = {0};
    block.user_mcode = Fan_On;
    CHECK(grbl.user_mcode.validate(&block) == Status_OK);
    grbl.user_mcode.execute(STATE_CHECK_MODE, &block);
    CHECK(delayed_task && outputs[0]);
    grbl.user_mcode.execute(STATE_IDLE, &block);
    CHECK(delayed_task == NULL && delayed_ms == 0 && outputs[0]);
    CHECK(fan_get_state(0) && !fan_get_state(1));
    grbl.on_program_completed((program_flow_t)0, false);
    CHECK(completed_calls == 2 && delayed_task && delayed_ms == 30000);
    run_delayed_fan();
    CHECK(!outputs[0] && !fan_get_state(0));
    return 0;
}
