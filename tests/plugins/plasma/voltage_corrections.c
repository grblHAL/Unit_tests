#include "plasma_host.h"
int main(void)
{
    plasma_boot();
    plasma_state = STATE_CYCLE;
    plasma_motor->set_state(plasma_motor, (spindle_state_t){.on = On}, 500);
    plasma_feed(600, 600);
    plasma_tick(3100);
    CHECK(!plasma_steps);
    plasma_voltage = 116;
    plasma_tick(500);
    CHECK(plasma_up_steps > 0 && !plasma_down_steps && !plasma_holds);
    plasma_voltage = 120;
    plasma_tick(500);
    unsigned stopped = plasma_steps;
    plasma_tick(100);
    CHECK(plasma_steps == stopped);
    plasma_voltage = 124;
    plasma_tick(500);
    CHECK(plasma_down_steps > 0 && !plasma_holds);
    return 0;
}
