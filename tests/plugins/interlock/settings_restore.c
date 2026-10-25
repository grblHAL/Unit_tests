#include "interlock_host.h"
int main(void)
{
    il_start();
    for (unsigned i = 0; i < 4; i++)
    {
        CHECK(il_float(900 + i, i) == Status_OK && il_float(912 + i, i) == Status_OK);
        il_int(904 + i, 1);
        il_int(908 + i, 0);
    }
    unsigned before = saves;
    registered_settings->restore();
    CHECK(saves == before + 1);
    for (unsigned i = 0; i < 4; i++)
        CHECK(il_read_float(900 + i) == -1 && il_read_float(912 + i) == -1 &&
              il_read_int(904 + i) == 0 && il_read_int(908 + i) == 1);
    registered_settings->load();
    levels[Port_Input][0] = 1;
    il_command(true);
    spindle_state_t state = {.on = 1};
    grbl.on_spindle_programmed(&spindle, state, 1000, SpindleSpeedMode_RPM);
    hal.port.digital_out(0, true);
    CHECK(hardware_spindles == 1 && hardware_outputs == 1 && output_value && resets == 0);
    return 0;
}
