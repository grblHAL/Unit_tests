#include "pca_host.h"
grbl_hal_t hal;
io_digital_t outputs;
bool bus_ok = true, device_present = true;
unsigned starts, probes, writes, registrations, enumerations;
uint8_t register_values[4], pin_base;
static void native_pins(bool low_level, pin_info_ptr callback, void *data)
{
    (void)low_level;
    enumerations++;
    for (unsigned i = 0; i < 2; i++)
    {
        xbar_t pin = {.group = PinGroup_AuxOutput, .function = Output_Aux0 + i};
        callback(&pin, data);
    }
}
void start_expander(void)
{
    void pca9654e_init(void);
    hal.enumerate_pins = native_pins;
    pca9654e_init();
}
i2c_cap_t i2c_start(void)
{
    starts++;
    return (i2c_cap_t){.started = bus_ok};
}
bool i2c_probe(i2c_address_t address)
{
    CHECK(address == 0x20);
    probes++;
    return device_present;
}
bool i2c_send(i2c_address_t address, uint8_t *data, size_t size, bool block)
{
    CHECK(address == 0x20 && size == 2 && block);
    CHECK(data[0] >= 1 && data[0] <= 3);
    if (writes < 3)
    {
        const uint8_t order[] = {3, 2, 1};
        CHECK(data[0] == order[writes] && data[1] == 0);
    }
    register_values[data[0]] = data[1];
    writes++;
    return true;
}
bool ioports_add_digital(io_digital_t *ports)
{
    CHECK(registrations == 0 && ports->ports->external);
    CHECK(ports->ports->out.n_ports == 8 && ports->ports->in.n_ports == 0);
    CHECK(ports->digital_out && ports->get_pin_info && ports->set_pin_description);
    ports->ports->out.pin_base = pin_base;
    outputs = *ports;
    registrations++;
    return true;
}
void ioport_save_output_settings(xbar_t *pin, gpio_out_config_t *config)
{
    (void)pin;
    (void)config;
    CHECK(false);
}
