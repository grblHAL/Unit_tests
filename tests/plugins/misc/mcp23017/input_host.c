#include "input_host.h"
grbl_hal_t hal;
system_t sys;
io_digital_t ports;
unsigned reads, sends, irq_claims;
uint16_t sample, output_value;
uint8_t device_registers[22];
static void enumerate(bool low_level, pin_info_ptr callback, void *data)
{
    (void)low_level;
    xbar_t input = {.group = PinGroup_AuxInput, .function = Input_Aux1};
    xbar_t output = {.group = PinGroup_AuxOutput, .function = Output_Aux1};
    callback(&input, data);
    callback(&output, data);
}
static bool irq_claim(irq_type_t type, uint_fast8_t id, irq_callback_ptr callback)
{
    CHECK(type == IRQ_I2C_Strobe && id == 0 && callback);
    irq_claims++;
    return false;
}
void start_inputs(void)
{
    void mcp23017_init(void);
    hal.enumerate_pins = enumerate;
    hal.irq_claim = irq_claim;
    mcp23017_init();
    CHECK(ports.ports && irq_claims == 1 && reads == 1);
}
i2c_cap_t i2c_start(void) { return (i2c_cap_t){.started = true}; }
bool i2c_probe(i2c_address_t address)
{
    CHECK(address == 0x20);
    return true;
}
bool i2c_send(i2c_address_t address, uint8_t *data, size_t size, bool block)
{
    CHECK(address == 0x20 && block && size >= 2 && size <= 3 &&
          data[0] + size - 1 <= sizeof(device_registers));
    for (unsigned i = 1; i < size; i++)
        device_registers[data[0] + i - 1] = data[i];
    if (data[0] == 0x12)
        output_value = data[1];
    sends++;
    return true;
}
bool i2c_transfer(i2c_transfer_t *transfer, bool read)
{
    CHECK(read && transfer->address == 0x20 && transfer->cmd_bytes == 1);
    CHECK(transfer->cmd == INPUT_REGISTER && transfer->count == INPUT_COUNT / 8 && transfer->data);
    transfer->data[0] = sample & 255;
    if (transfer->count == 2)
        transfer->data[1] = sample >> 8;
    reads++;
    return true;
}
bool ioports_add_digital(io_digital_t *bank)
{
    CHECK(!ports.ports && bank->ports->external && bank->ports->in.n_ports == INPUT_COUNT);
#if MCP23017_ENABLE == 1
    CHECK(bank->ports->out.n_ports == 8 && bank->digital_out);
#else
    CHECK(bank->ports->out.n_ports == 0 && !bank->digital_out);
#endif
    CHECK(bank->wait_on_input && bank->register_interrupt_handler);
    ports = *bank;
    return true;
}
void ioport_save_input_settings(xbar_t *pin, gpio_in_config_t *config)
{
    (void)pin;
    (void)config;
    CHECK(false);
}
void ioport_save_output_settings(xbar_t *pin, gpio_out_config_t *config)
{
    (void)pin;
    (void)config;
    CHECK(false);
}
bool task_add_immediate(foreground_task_ptr fn, void *data)
{
    (void)fn;
    (void)data;
    CHECK(false);
    return false;
}
bool protocol_execute_realtime(void)
{
    CHECK(false);
    return false;
}
