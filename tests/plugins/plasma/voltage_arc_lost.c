#include "plasma_host.h"
int main(void)
{
    plasma_boot();
    plasma_state = STATE_CYCLE;
    plasma_motor->set_state(plasma_motor, (spindle_state_t){.on = On}, 500);
    plasma_feed(600, 600);
    plasma_tick(3100);
    plasma_voltage = 116;
    plasma_tick(400);
    CHECK(plasma_steps > 0 && !plasma_holds);
    plasma_input("Arc ok", false);
    plasma_tick(100);
    CHECK(plasma_holds == 1 && plasma_state == STATE_HOLD);
    plasma_tick(100);
    CHECK(plasma_holds == 1);
    return 0;
}
