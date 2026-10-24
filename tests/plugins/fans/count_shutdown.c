#include "fan_host.h"

int main(void)
{
    available_ports = FANS_ENABLE;
    load_fans();
    *(float *)fan_setting(Setting_Fan0OffDelay)->value = 0.25f;
    for (unsigned i = 0; i < FANS_ENABLE; i++)
        fan_set_state(i, true);
    grbl.on_program_completed((program_flow_t)0, false);
    CHECK(completed_calls == 1 && delayed_task && delayed_ms == 15000);
    for (unsigned i = 0; i < FANS_ENABLE; i++)
        CHECK(outputs[i] == (i == 0) && fan_get_state(i) == (i == 0));
    run_delayed_fan();
    CHECK(!outputs[0] && !fan_get_state(0));
    for (unsigned i = 0; i < FANS_ENABLE; i++)
        fan_set_state(i, true);
    hal.driver_reset();
    CHECK(reset_calls == 1 && delayed_task == NULL);
    for (unsigned i = 0; i < FANS_ENABLE; i++)
        CHECK(!outputs[i] && !fan_get_state(i));
    return 0;
}
