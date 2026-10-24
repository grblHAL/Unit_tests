#include "event_host.h"
int main(void)
{
    claimed_mask = 1;
    missing_mask = 2;
    prepare_events();
    event_details->restore();
    const setting_detail_t *port = &event_details->settings[1];
    CHECK(((setting_set_float_ptr)port->value)(Setting_ActionPortBase + 2, -1) == Status_OK);
    event_details->save();
    event_details->load();
    run_event_startup();
    setting_get_float_ptr get = (setting_get_float_ptr)port->get_value;
    for (unsigned i = 0; i < 3; i++)
    {
        CHECK(get(Setting_ActionPortBase + i) == -1);
        bind_event(i, 3);
    }
    bind_event(3, 4);
    hal.coolant.set_state((coolant_state_t){.mist = On});
    CHECK(!levels[0] && !levels[1] && !levels[2] && !levels[3] && writes == 1);
    hal.coolant.set_state((coolant_state_t){.mist = On, .flood = On});
    CHECK(!levels[0] && !levels[1] && !levels[2] && levels[3] && writes == 2);
    return 0;
}
