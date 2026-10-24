#include "fan_host.h"
int main(void)
{
 load_fans(); *(float *)fan_setting(Setting_Fan0OffDelay)->value = 0.25f;
 fan_set_state(0, true); fan_set_state(1, true);
 grbl.on_program_completed((program_flow_t)0, false);
 CHECK(completed_calls == 1 && outputs[0] && !outputs[1] && delayed_task && delayed_ms == 15000);
 parser_block_t block = {0}; block.user_mcode = Fan_Off;
 grbl.user_mcode.execute(STATE_IDLE, &block); CHECK(!outputs[0] && delayed_task == NULL);
 fan_set_state(0, true); grbl.on_program_completed((program_flow_t)0, false);
 CHECK(outputs[0] && delayed_task); run_delayed_fan(); CHECK(!outputs[0] && !fan_get_state(0));
 return 0;
}
