#include "support/ioports_assignment_host.h"

int main(void)
{
    xbar_t *pin = prepare_assignment(Port_Output);
    CHECK(ioport_set_function(pin, Output_CoolantFlood, (driver_caps_t){0}));
    CHECK(hal.coolant_cap.flood);
    char inverted_aux[] = "2";
    CHECK(settings_store_setting(Settings_IoPort_InvertOut, inverted_aux) == Status_OK);
    gpio_out_config_t config = {.inverted = true, .open_drain = true};
    ioport_save_output_settings(pin, &config);
    CHECK(settings.ioport.invert_out.mask == 2 && settings.ioport.od_enable_out.mask == 1);
    settings_t saved;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&saved, NVS_ADDR_GLOBAL, sizeof(saved), true));
    CHECK(saved.ioport.invert_out.mask == 2 && saved.ioport.od_enable_out.mask == 1);
    config.inverted = false;
    config.open_drain = false;
    ioport_save_output_settings(pin, &config);
    CHECK(settings.ioport.invert_out.mask == 2 && settings.ioport.od_enable_out.mask == 0);
    CHECK(pin->function == Output_CoolantFlood && assignment_calls == 1);
    CHECK(ioport_digital_out(1, true));
    CHECK(physical_output == 1 && output_value);
    return EXIT_SUCCESS;
}
