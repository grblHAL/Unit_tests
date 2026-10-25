#include "mcp_host.h"
grbl_hal_t hal;
io_digital_t bank;
bool bus_ok = true, probe_ok = true;
unsigned starts, probes, writes, registrations;
uint16_t gpio;
uint8_t pin_base;
static void enumerate(bool low_level, pin_info_ptr callback, void *data)
{
    (void)low_level;
    xbar_t pin = {.group = PinGroup_AuxOutput, .function = Output_Aux1};
    callback(&pin, data);
}
void start_mcp(void)
{
    void mcp23017_init(void);
    hal.enumerate_pins = enumerate;
    mcp23017_init();
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
    return probe_ok;
}
bool i2c_send(i2c_address_t address, uint8_t *data, size_t size, bool block)
{
    CHECK(address == 0x20 && block);
    if (writes == 0)
        CHECK(size == 2 && data[0] == 0x0a && data[1] == 4);
    else if (writes == 1)
        CHECK(size == 3 && data[0] == 0 && data[1] == 0 && data[2] == 0);
    else
    {
        CHECK(size == 3 && data[0] == 0x12);
        gpio = data[1] | ((uint16_t)data[2] << 8);
    }
    writes++;
    return true;
}
bool ioports_add_digital(io_digital_t *ports)
{
    CHECK(!registrations && ports->ports->external);
    CHECK(ports->ports->out.n_ports == 16 && ports->ports->in.n_ports == 0);
    CHECK(ports->digital_out && !ports->wait_on_input);
    ports->ports->out.pin_base = pin_base;
    bank = *ports;
    registrations++;
    return true;
}
void ioport_save_output_settings(xbar_t *pin, gpio_out_config_t *config)
{
    (void)pin;
    (void)config;
    CHECK(false);
}
