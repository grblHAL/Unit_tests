#include "fan_host.h"
int main(void)
{
 prepare_fans(); fans_init(); CHECK(registered_settings); registered_settings->restore();
 const setting_detail_t *port0 = fan_setting(Setting_FanPort0), *port1 = fan_setting(Setting_FanPort1);
 CHECK(port0->is_available(port0, 0) && port1->is_available(port1, 0));
 CHECK(((setting_set_float_ptr)port0->value)(port0->id, 1) == Status_OK);
 CHECK(((setting_set_float_ptr)port1->value)(port1->id, -1) == Status_OK);
 CHECK(((setting_get_float_ptr)port0->get_value)(port0->id) == 1);
 CHECK(((setting_get_float_ptr)port1->get_value)(port1->id) == -1);
 const setting_detail_t *link = fan_setting(Setting_FanToSpindleLink);
 CHECK(((setting_get_int_ptr)link->get_value)(link->id) == 0);
 registered_settings->save(); CHECK(saved == 2); registered_settings->load(); CHECK(warnings == 1);
 fan_set_state(0, true); CHECK(outputs[1] && !outputs[0] && fan_get_state(0));
 fan_set_state(1, true); CHECK(output_calls == 1 && !fan_get_state(1));
 return 0;
}
