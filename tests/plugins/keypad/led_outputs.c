#include "led_host.h"
int main(void)
{
    led_prepare();
    display_init();
    CHECK(grbl.on_spindle_select(&led_spindle) && led_selects == 1);
    led_spindle.set_state(&led_spindle, (spindle_state_t){.on = On}, 500);
    CHECK(led_spindles == 1 && led_spindle_state.on && led_bytes[2][1] == 4);
    hal.coolant.set_state((coolant_state_t){.flood = On, .mist = On});
    CHECK(led_coolants == 1 && led_coolant_state.flood && led_coolant_state.mist);
    CHECK(led_bytes[3][1] == 28);
    grbl.on_state_change(STATE_CYCLE);
    CHECK(led_bytes[4][1] == 29);
    led_spindle.set_state(&led_spindle, (spindle_state_t){0}, 500);
    CHECK(led_bytes[5][1] == 25 && led_spindles == 2);
    hal.coolant.set_state((coolant_state_t){0});
    CHECK(led_bytes[6][1] == 1 && led_coolants == 2);
    return 0;
}
