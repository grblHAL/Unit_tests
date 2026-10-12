#include "support/engine_host.h"
#include "ioports.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    xbar_t pin = { .function = Input_Probe };
    gpio_in_config_t config = { .inverted = true };
    ioport_save_input_settings(&pin, &config);
    CHECK(settings.probe.invert_probe_pin);
    settings_t stored;
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&stored, NVS_ADDR_GLOBAL, sizeof(stored), true));
    CHECK(stored.probe.invert_probe_pin);
    return EXIT_SUCCESS;
}
