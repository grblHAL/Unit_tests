#include "therm_host.h"
int main(void)
{
    therm_prepare();
    thermistor_init();
    CHECK(registered_settings && registered_commands && saves == 0 && claims == 0);
    registered_settings->load();
    CHECK(saves == 1 && claims == 0 && warnings == 0);
    const setting_detail_t *port = &registered_settings->settings[0];
    CHECK(port->id == 455 && ((setting_get_float_ptr)port->get_value)(455) == -1);
    CHECK(therm_command("THRMTEMP", STATE_IDLE, NULL) == Status_InvalidStatement);
    CHECK(therm_command("THRMCAL", STATE_IDLE, "25") == Status_InvalidStatement);
    therm_report(true);
    CHECK(strcmp(output, "|previous") == 0 && reads == 0 && stops == 0);
    return 0;
}
