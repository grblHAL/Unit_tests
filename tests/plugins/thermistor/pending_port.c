#include "therm_host.h"
int main(void)
{
    therm_start(true);
    const setting_detail_t *port = &registered_settings->settings[0];
    CHECK(port->id == 455 && port->type == Setting_NonCoreFn && port->get_value &&
          port->is_available && port->is_available(port, 0) && port->flags.reboot_required);
    setting_get_float_ptr get = (setting_get_float_ptr)port->get_value;
    setting_set_float_ptr set = (setting_set_float_ptr)port->value;
    CHECK(get(455) == 1 && claims == 1);
    CHECK(set(455, 2) == Status_AuxiliaryPortUnavailable && get(455) == 1);
    CHECK(set(455, -1) == Status_OK && get(455) == -1);
    registered_settings->save();
    CHECK(therm_command("THRMTEMP", STATE_IDLE, NULL) == Status_OK && strstr(output, "25.0 degC") &&
          claims == 1 && reads == 1);
    therm_report(true);
    CHECK(strstr(output, "|TH0:25.0") && claims == 1 && reads == 2);
    return 0;
}
