#include "interlock_host.h"
int main(void)
{
    il_start();
    CHECK(il_float(912, 1) == Status_OK && il_float(913, 2) == Status_OK);
    spindle_state_t state = {.on = 1};
    grbl.on_spindle_programmed(&spindle, state, 1000, SpindleSpeedMode_RPM);
    hal.port.digital_out(1, true);
    hal.port.digital_out(2, false);
    CHECK(hardware_outputs == 0 && resets == 2 && warnings == 0);
    CHECK(il_float(912, -1) == Status_OK && il_read_float(912) == -1);
    hal.port.digital_out(1, true);
    CHECK(hardware_outputs == 1 && output_value);
    hal.port.digital_out(2, true);
    CHECK(hardware_outputs == 1 && resets == 3);
    CHECK(il_float(913, -1) == Status_OK && il_read_float(913) == -1);
    hal.port.digital_out(2, false);
    CHECK(hardware_outputs == 2 && !output_value && resets == 3);
    return 0;
}
