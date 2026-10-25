#include "led_host.h"
int main(void)
{
    led_prepare();
    display_init();
    led_send_ok = false;
    grbl.on_state_change(STATE_CYCLE);
    CHECK(led_states == 1 && led_bytes[2][1] == 1);
    led_send_ok = true;
    grbl.on_state_change(STATE_HOLD);
    CHECK(led_states == 2 && led_bytes[3][1] == 2);
    hal.coolant.set_state((coolant_state_t){.flood = On});
    CHECK(led_coolants == 1 && led_bytes[4][1] == 10);
    return 0;
}
