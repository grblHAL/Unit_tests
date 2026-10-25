#include "event_host.h"
int main(void)
{
    prepare_events();
    event_details->restore();
    const setting_detail_t *port = &event_details->settings[1];
    setting_set_float_ptr set = (setting_set_float_ptr)port->value;
    setting_get_float_ptr get = (setting_get_float_ptr)port->get_value;
    CHECK(set(Setting_ActionPortBase, 3) == Status_OK);
    CHECK(set(Setting_ActionPortBase + 3, 0) == Status_OK);
    event_details->save();
    CHECK(set(Setting_ActionPortBase, 0) == Status_OK);
    event_details->load();
    CHECK(saves == 2 && get(Setting_ActionPortBase) == 3 && get(Setting_ActionPortBase + 3) == 0);
    run_event_startup();
    bind_event(0, 3);
    hal.coolant.set_state((coolant_state_t){.mist = On});
    CHECK(levels[3] && !levels[0] && writes == 1);
    CHECK(set(Setting_ActionPortBase, 0) == Status_OK);
    event_details->save();
    hal.coolant.set_state((coolant_state_t){0});
    CHECK(!levels[3]);
    hal.coolant.set_state((coolant_state_t){.mist = On});
    CHECK(levels[3] && !levels[0] && writes == 3 && saves == 3);
    return 0;
}
