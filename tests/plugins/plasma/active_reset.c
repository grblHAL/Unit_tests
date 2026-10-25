#include "plasma_host.h"
int main(void)
{
    plasma_boot();
    plasma_state = STATE_CYCLE;
    plasma_motor->set_state(plasma_motor, (spindle_state_t){.on = On}, 500);
    plasma_feed(600, 600);
    plasma_tick(3100);
    plasma_input("Cutter up", true);
    plasma_tick(400);
    CHECK(plasma_steps > 0);
    plasma_state = STATE_IDLE;
    grbl.on_reset();
    hal.driver_reset();
    plasma_tick(100);
    unsigned count = plasma_steps;
    plasma_tick(100);
    CHECK(plasma_steps == count && plasma_resets == 1 && !plasma_motor_claimed);
    return 0;
}
