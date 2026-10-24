#include "support/ioports_assignment_host.h"

int main(void)
{
    xbar_t *pin = prepare_assignment(Port_Input);
    CHECK(ioport_set_function(pin, Input_Probe, (driver_caps_t){0}));
    char inverted_aux[] = "2";
    CHECK(settings_store_setting(Settings_IoPort_InvertIn, inverted_aux) == Status_OK);
    gpio_in_config_t config = {.inverted = true, .pull_mode = PullMode_None};
    ioport_save_input_settings(pin, &config);
    CHECK(settings.probe.invert_probe_pin);
    CHECK(settings.ioport.invert_in.mask == 2);
    CHECK(settings.ioport.pullup_disable_in.mask == 1);
    settings_t saved;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&saved, NVS_ADDR_GLOBAL, sizeof(saved), true));
    CHECK(saved.probe.invert_probe_pin && saved.ioport.invert_in.mask == 2);
    CHECK(saved.ioport.pullup_disable_in.mask == 1);
    config.inverted = false;
    config.pull_mode = PullMode_Up;
    ioport_save_input_settings(pin, &config);
    CHECK(!settings.probe.invert_probe_pin && settings.ioport.invert_in.mask == 2);
    CHECK(settings.ioport.pullup_disable_in.mask == 0);
    CHECK(pin->function == Input_Probe && assignment_calls == 1);
    return EXIT_SUCCESS;
}
