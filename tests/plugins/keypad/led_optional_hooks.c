#include "led_host.h"
int main(void)
{
    led_prepare();
    grbl.on_state_change = NULL;
    grbl.on_spindle_select = NULL;
    display_init();
    grbl.on_state_change(STATE_HOLD);
    CHECK(led_states == 0 && led_bytes[2][1] == 2);
    CHECK(grbl.on_spindle_select(&led_spindle) && led_selects == 0);
    led_spindle.set_state(&led_spindle, (spindle_state_t){.on = On}, 500);
    CHECK(led_spindles == 1 && led_bytes[3][1] == 6);
    return 0;
}
