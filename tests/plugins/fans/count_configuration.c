#include "fan_host.h"
#include <stdio.h>

int main(void)
{
    available_ports = FANS_ENABLE;
    load_fans();
    CHECK(saved == 1 && warnings == 0);
    unsigned ports = 0;
    for (unsigned i = 0; i < registered_settings->n_settings; i++)
    {
        const setting_detail_t *setting = &registered_settings->settings[i];
        if (setting->id >= Setting_FanPort0 && setting->id <= Setting_FanPort3)
        {
            CHECK(setting->id < Setting_FanPort0 + FANS_ENABLE);
            CHECK(setting->is_available(setting, 0));
            CHECK(((setting_get_float_ptr)setting->get_value)(setting->id) ==
                  setting->id - Setting_FanPort0);
            ports++;
        }
    }
    CHECK(ports == FANS_ENABLE);
    const setting_detail_t *link = fan_setting(Setting_FanToSpindleLink);
    CHECK(link->datatype == (FANS_ENABLE == 1 ? Format_Bool : Format_Bitfield));
    for (unsigned i = 0; i < FANS_ENABLE; i++)
    {
        parser_block_t block = {0};
        block.user_mcode = Fan_On;
        block.words.p = On;
        block.values.p = i;
        parser_block_t validated = block;
        CHECK(grbl.user_mcode.validate(&validated) == Status_OK && !validated.words.p);
        grbl.user_mcode.execute(STATE_IDLE, &block);
        CHECK(outputs[i] && fan_get_state(i));
    }
    CHECK(output_calls == FANS_ENABLE);
    grbl.on_report_options(false);
    char expected[24];
    snprintf(expected, sizeof(expected), "[FANS:%u]", FANS_ENABLE);
    CHECK(strstr(fan_output, expected));
    fan_output[0] = 0;
    grbl.on_realtime_report(hal.stream.write, (report_tracking_flags_t){.fan = On});
    snprintf(expected, sizeof(expected), "|Fan:%u", (1u << FANS_ENABLE) - 1);
    CHECK(strcmp(fan_output, expected) == 0);
    return 0;
}
