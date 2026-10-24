#include "fan_host.h"
static void spindle_state(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{ CHECK(spindle); (void)state; CHECK(rpm == 500); spindle_calls++; }
int main(void)
{
 load_fans();
 const setting_detail_t *link = fan_setting(Setting_FanToSpindleLink);
 CHECK(((setting_set_int_ptr)link->value)(link->id, 1) == Status_OK);
 *(float *)fan_setting(Setting_Fan0OffDelay)->value = 0.5f;
 spindle_ptrs_t spindle = {.set_state = spindle_state}; CHECK(grbl.on_spindle_select(&spindle));
 spindle.set_state(&spindle, (spindle_state_t){.on = On}, 500); CHECK(outputs[0] && !outputs[1]);
 spindle.set_state(&spindle, (spindle_state_t){0}, 500);
 CHECK(delayed_task && delayed_ms == 30000 && outputs[0]); run_delayed_fan(); CHECK(!outputs[0]);
 fan_set_state(0, true); spindle.set_state(&spindle, (spindle_state_t){0}, 500);
 CHECK(outputs[0] && delayed_task == NULL); CHECK(spindle_calls == 3);
 return 0;
}
