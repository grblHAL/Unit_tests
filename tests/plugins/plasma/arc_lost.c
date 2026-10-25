#include "plasma_host.h"
int main(void)
{
    plasma_boot();
    plasma_state = STATE_CYCLE;
    plasma_motor->set_state(plasma_motor, (spindle_state_t){.on = On}, 500);
    plasma_tick(3100);
    plasma_input("Arc ok", false);
    plasma_tick(5);
    CHECK(plasma_holds == 1 && plasma_state == STATE_HOLD);
    return 0;
}
