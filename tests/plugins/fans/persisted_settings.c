#include "fan_host.h"

int main(void)
{
    prepare_fans();
    fans_init();
    CHECK(registered_settings);
    registered_settings->restore();
    const setting_detail_t *port0 = fan_setting(Setting_FanPort0);
    const setting_detail_t *port1 = fan_setting(Setting_FanPort1);
    float *delay = fan_setting(Setting_Fan0OffDelay)->value;
    CHECK(((setting_set_float_ptr)port0->value)(port0->id, 1) == Status_OK);
    CHECK(((setting_set_float_ptr)port1->value)(port1->id, 0) == Status_OK);
    *delay = 0.125f;
    registered_settings->save();
    CHECK(saved == 2);

    // Change the live settings before the first load to prove that NVS is read.
    CHECK(((setting_set_float_ptr)port0->value)(port0->id, 0) == Status_OK);
    CHECK(((setting_set_float_ptr)port1->value)(port1->id, 1) == Status_OK);
    *delay = 0.0f;
    registered_settings->load();
    CHECK(saved == 2 && warnings == 0 && *delay == 0.125f);
    CHECK(((setting_get_float_ptr)port0->get_value)(port0->id) == 1);
    CHECK(((setting_get_float_ptr)port1->get_value)(port1->id) == 0);
    fan_set_state(0, true);
    CHECK(outputs[1] && !outputs[0]);
    fan_set_state(1, true);
    grbl.on_program_completed((program_flow_t)0, false);
    CHECK(completed_calls == 1 && outputs[1] && !outputs[0]);
    CHECK(delayed_task && delayed_ms == 7500);
    run_delayed_fan();
    CHECK(!outputs[0] && !outputs[1] && !fan_get_state(0));
    return 0;
}
