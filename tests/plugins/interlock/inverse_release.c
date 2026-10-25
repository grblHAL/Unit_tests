#include "interlock_host.h"
int main(void)
{
    il_start();
    CHECK(il_float(912, 2) == Status_OK);
    spindle_state_t s = {0};
    s.on = 1;
    grbl.on_spindle_programmed(&spindle, s, 1000, SpindleSpeedMode_RPM);
    hal.port.digital_out(1, true);
    CHECK(hardware_outputs == 1);
    s.on = 0;
    grbl.on_spindle_programmed(&spindle, s, 1000, SpindleSpeedMode_RPM);
    hal.port.digital_out(2, false);
    CHECK(hardware_outputs == 2 && !output_value && resets == 0);
    return 0;
}
