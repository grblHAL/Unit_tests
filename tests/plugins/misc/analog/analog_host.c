#include "analog_host.h"
#include <string.h>
grbl_hal_t hal;
io_analog_t bank;
bool start_ok = true, probe_ok = true, send_ok = true;
unsigned starts, probes, sends, reads, registrations, native_enumerations;
uint16_t sample = 0xabc;
uint8_t packet[3];

static void enumerate(bool low_level, pin_info_ptr callback, void *data)
{
    (void)low_level;
    native_enumerations++;
    xbar_t pin = {.group = DEVICE_GROUP, .function = DEVICE_FUNCTION + 2};
    callback(&pin, data);
}
static void delay(uint32_t ms, void (*callback)(void)) { CHECK(ms == 2 && callback == NULL); }
void prepare_analog(void)
{
    hal.enumerate_pins = enumerate;
    hal.delay_ms = delay;
}
void initialize_analog(void)
{
#ifdef MCP4725_ENABLE
    void mcp4725_init(void);
    mcp4725_init();
#else
    void mcp3221_init(void);
    mcp3221_init();
#endif
}
i2c_cap_t i2c_start(void)
{
    starts++;
    return (i2c_cap_t){.started = start_ok};
}
bool i2c_probe(i2c_address_t address)
{
    CHECK(address == DEVICE_ADDRESS);
    probes++;
    return probe_ok;
}
bool i2c_send(i2c_address_t address, uint8_t *data, size_t size, bool block)
{
    CHECK(block && size > 0 && size <= sizeof(packet));
    if (address == 0)
    {
        CHECK(size == 1 && sends < 2);
        CHECK(data[0] == (sends == 0 ? 0x06 : 0x09));
    }
    else
        CHECK(address == DEVICE_ADDRESS && size == 3 && data[0] == 0x40);
    memcpy(packet, data, size);
    sends++;
    return send_ok;
}
bool i2c_receive(i2c_address_t address, uint8_t *data, size_t size, bool block)
{
    CHECK(address == DEVICE_ADDRESS && block);
#ifdef MCP4725_ENABLE
    CHECK(size == 5);
    memset(data, 0, size);
    data[1] = sample >> 4;
    data[2] = (sample & 15) << 4;
#else
    CHECK(size == 2);
    data[0] = sample >> 8;
    data[1] = sample & 255;
#endif
    reads++;
    return true;
}
bool ioports_add_analog(io_analog_t *ports)
{
    CHECK(registrations == 0 && ports->ports->external && ports->get_pin_info);
#ifdef MCP4725_ENABLE
    CHECK(ports->ports->out.n_ports == 1 && ports->ports->in.n_ports == 0);
    CHECK(ports->analog_out && !ports->wait_on_input);
    ports->ports->out.pin_base = 3;
#else
    CHECK(ports->ports->in.n_ports == 1 && ports->ports->out.n_ports == 0);
    CHECK(ports->wait_on_input && !ports->analog_out);
    ports->ports->in.pin_base = 3;
#endif
    bank = *ports;
    registrations++;
    return true;
}
