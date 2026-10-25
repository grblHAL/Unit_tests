#include "plasma_host.h"
int main(void)
{
    plasma_boot();
    plasma_state = STATE_CYCLE;
    plasma_motor->set_state(plasma_motor, (spindle_state_t){.on = On}, 500);
    CHECK(plasma_torch_on && plasma_torch_starts == 1 && plasma_waits == 1 && plasma_motor_claimed);
    plasma_tick(3100);
    CHECK(!plasma_holds && !plasma_steps);
    plasma_state = STATE_IDLE;
    plasma_motor->set_state(plasma_motor, (spindle_state_t){0}, 0);
    plasma_tick(10);
    CHECK(!plasma_torch_on && !plasma_motor_claimed && plasma_torch_stops == 1);
    return 0;
}
