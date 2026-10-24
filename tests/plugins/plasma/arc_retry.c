#include "plasma_host.h"
int main(void)
{
    plasma_boot();
    plasma_fail_waits = 2;
    plasma_state = STATE_CYCLE;
    plasma_motor->set_state(plasma_motor, (spindle_state_t){.on = On}, 500);
    CHECK(plasma_waits == 3 && plasma_torch_starts == 3 && plasma_torch_stops == 2 &&
          plasma_torch_on && !plasma_holds);
    plasma_state = STATE_IDLE;
    plasma_motor->set_state(plasma_motor, (spindle_state_t){0}, 0);
    return 0;
}
