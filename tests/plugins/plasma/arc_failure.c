#include "plasma_host.h"
int main(void)
{
    plasma_boot();
    plasma_wait_ok = false;
    plasma_state = STATE_CYCLE;
    plasma_motor->set_state(plasma_motor, (spindle_state_t){.on = On}, 500);
    CHECK(plasma_waits == 3 && plasma_torch_starts == 3 && plasma_torch_stops == 3 &&
          !plasma_torch_on);
    CHECK(plasma_holds == 1 && plasma_state == STATE_HOLD && !plasma_steps &&
          !plasma_motor_claimed);
    return 0;
}
