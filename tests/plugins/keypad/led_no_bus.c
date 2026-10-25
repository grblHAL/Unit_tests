#include "led_host.h"
int main(void)
{
    led_prepare();
    led_bus_ok = false;
    display_init();
    CHECK(led_probes == 0 && led_warnings == 1 && led_writes == 0);
    grbl.on_state_change(STATE_CYCLE);
    hal.coolant.set_state((coolant_state_t){.mist = On});
    CHECK(led_states == 1 && led_coolants == 1 && led_writes == 0);
    return 0;
}
