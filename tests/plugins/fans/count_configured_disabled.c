#include "fan_host.h"
#include <stdio.h>

int main(void)
{
    available_ports = FANS_ENABLE;
    prepare_fans();
    fans_init();
    CHECK(registered_settings);
    registered_settings->restore();
    const setting_detail_t *port = fan_setting(Setting_FanPort0 + FANS_ENABLE - 1);
    CHECK(((setting_set_float_ptr)port->value)(port->id, -1) == Status_OK);
    registered_settings->save();
    registered_settings->load();
    CHECK(saved == 2 && warnings == 1 && output_calls == 0);
    for (unsigned i = 0; i < FANS_ENABLE; i++)
    {
        fan_set_state(i, true);
        CHECK(fan_get_state(i) == (i < FANS_ENABLE - 1));
        CHECK(outputs[i] == (i < FANS_ENABLE - 1));
    }
    CHECK(output_calls == FANS_ENABLE - 1);
    grbl.on_report_options(false);
    char expected[24];
    snprintf(expected, sizeof(expected), "[FANS:%u]", FANS_ENABLE - 1);
    CHECK(strstr(fan_output, expected));
    return 0;
}
