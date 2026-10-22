#include "support/multi_bank_ioports_host.h"

int main(void)
{
    prepare_multi_bank_ioports();
    xbar_t *input = ioport_get_info(Port_Digital, Port_Input, 3);
    xbar_t *output = ioport_get_info(Port_Digital, Port_Output, 3);
    CHECK(input == &bank_digital_pins[1][Port_Input][1]);
    CHECK(output == &bank_digital_pins[1][Port_Output][1]);
    settings.ioport.invert_in.mask = settings.ioport.invert_out.mask = 1;
    settings.ioport.pullup_disable_in.mask = settings.ioport.od_enable_out.mask = 1;
    gpio_in_config_t in_config = {.inverted = true, .pull_mode = PullMode_Down};
    gpio_out_config_t out_config = {.inverted = true, .open_drain = true};
    ioport_save_input_settings(input, &in_config);
    ioport_save_output_settings(output, &out_config);
    CHECK(settings.ioport.invert_in.mask == 9);
    CHECK(settings.ioport.invert_out.mask == 9);
    CHECK(settings.ioport.pullup_disable_in.mask == 9);
    CHECK(settings.ioport.od_enable_out.mask == 9);
    settings_t stored;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&stored, NVS_ADDR_GLOBAL, sizeof(stored), true));
    CHECK(stored.ioport.invert_in.mask == 9 && stored.ioport.invert_out.mask == 9);
    CHECK(stored.ioport.pullup_disable_in.mask == 9 && stored.ioport.od_enable_out.mask == 9);

    in_config.inverted = false;
    in_config.pull_mode = PullMode_Up;
    out_config.inverted = out_config.open_drain = false;
    ioport_save_input_settings(input, &in_config);
    ioport_save_output_settings(output, &out_config);
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&stored, NVS_ADDR_GLOBAL, sizeof(stored), true));
    CHECK(stored.ioport.invert_in.mask == 1 && stored.ioport.invert_out.mask == 1);
    CHECK(stored.ioport.pullup_disable_in.mask == 1 && stored.ioport.od_enable_out.mask == 1);
    CHECK(bank_output_calls == 0 && bank_event_calls == 0);
    return EXIT_SUCCESS;
}
