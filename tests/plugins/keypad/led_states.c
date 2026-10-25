#include "led_host.h"
int main(void)
{
    led_prepare();
    display_init();
    CHECK(led_writes == 2 && led_bytes[0][0] == 3 && led_bytes[1][0] == 2);
    CHECK(led_bytes[0][1] == 0 && led_bytes[1][1] == 0);
    CHECK(led_blocking[0] && led_blocking[1]);
    grbl.on_state_change(STATE_CYCLE);
    CHECK(led_writes == 3 && led_bytes[2][0] == 1 && led_bytes[2][1] == 1);
    CHECK(!led_blocking[2]);
    grbl.on_state_change(STATE_CYCLE);
    CHECK(led_writes == 3 && led_states == 2);
    grbl.on_state_change(STATE_HOLD);
    CHECK(led_bytes[3][1] == 2);
    grbl.on_state_change(STATE_IDLE);
    CHECK(led_bytes[4][1] == 0 && led_states == 4);
    return 0;
}
