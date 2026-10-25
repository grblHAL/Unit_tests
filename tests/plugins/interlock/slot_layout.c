#include "interlock_host.h"
int main(void)
{
    const unsigned fwd = SPINDLE_INTERLOCK_FWD_SLOTS, inv = SPINDLE_INTERLOCK_INV_SLOTS;
    il_start();
    CHECK(registered_settings->n_settings == 3 * fwd + inv);
    for (unsigned i = 0; i < registered_settings->n_settings; i++)
    {
        const setting_detail_t *setting = &registered_settings->settings[i];
        CHECK(setting->id == 900 + i && setting->group == Group_AuxPorts && setting->name &&
              setting->value && setting->get_value);
    }
    CHECK(strcmp(registered_settings->settings[0].name, "Interlock FWD0 port") == 0 &&
          strcmp(registered_settings->settings[3 * fwd].name, "Interlock INV0 port") == 0);
    for (unsigned i = 0; i < fwd; i++)
    {
        CHECK(il_read_float(900 + i) == -1 && il_read_int(900 + fwd + i) == 0 &&
              il_read_int(900 + 2 * fwd + i) == 1);
        CHECK(il_float(900 + i, i) == Status_OK);
        il_int(900 + fwd + i, 0);
        il_int(900 + 2 * fwd + i, 1);
    }
    for (unsigned i = 0; i < inv; i++)
    {
        CHECK(il_read_float(900 + 3 * fwd + i) == -1);
        CHECK(il_float(900 + 3 * fwd + i, 2 + i) == Status_OK);
    }
    levels[Port_Input][fwd - 1] = 1;
    il_command(true);
    CHECK(hardware_spindles == 0 && resets == 1);
    levels[Port_Input][fwd - 1] = 0;
    il_command(true);
    CHECK(hardware_spindles == 1 && resets == 1);
    spindle_state_t state = {.on = 1};
    grbl.on_spindle_programmed(&spindle, state, 1000, SpindleSpeedMode_RPM);
    hal.port.digital_out(2 + inv - 1, true);
    CHECK(hardware_outputs == 0 && resets == 2);
    hal.port.digital_out(0, true);
    CHECK(hardware_outputs == 1 && output_value);
    return 0;
}
