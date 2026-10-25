#include "plasma_host.h"
int main(void)
{
    plasma_boot();
    plasma_state = STATE_CYCLE;
    plasma_motor->set_state(plasma_motor, (spindle_state_t){.on = On}, 500);
    plasma_feed(600, 600);
    plasma_tick(3100);
    plasma_input("Cutter up", true);
    plasma_tick(600);
    CHECK(plasma_up_steps > 0 && !plasma_down_steps);
    plasma_input("Cutter up", false);
    plasma_tick(600);
    unsigned count = plasma_steps;
    plasma_tick(100);
    CHECK(plasma_steps == count);
    plasma_input("Cutter down", true);
    plasma_tick(600);
    CHECK(plasma_down_steps > 0 && !plasma_holds);
    return 0;
}
