#include "led_host.h"
int main(void)
{
    led_prepare();
    led_probe_ok = false;
    display_init();
    CHECK(led_probes == 1 && led_warnings == 1 && led_writes == 0);
    CHECK(grbl.on_spindle_select(&led_spindle));
    led_spindle.set_state(&led_spindle, (spindle_state_t){.on = On}, 500);
    CHECK(led_spindles == 1 && led_writes == 0);
    return 0;
}
