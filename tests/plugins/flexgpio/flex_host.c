#include "flex_host.h"
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
io_digital_t bank;
bool start_ok = true, probe_ok = true, send_ok = true, receive_ok = true, claim_ok = true;
unsigned sends, receives, alarms, warnings, saved, chains, events;
bool inject_inputs, abort_on_realtime;
unsigned realtime_calls, delay_calls;
uint32_t delay_bits;
uint8_t event_port;
bool event_value;
uint32_t input_bits;
uint8_t last_packet[8];
size_t last_size;
static ioport_interrupt_callback_ptr irq_handler;
static struct
{
    foreground_task_ptr fn;
    void *data;
} tasks[64];
static unsigned pending;
i2c_cap_t i2c_start(void) { return (i2c_cap_t){.started = start_ok}; }
bool i2c_probe(i2c_address_t address)
{
    CHECK(address == 0x48);
    return probe_ok;
}
bool i2c_send(i2c_address_t address, uint8_t *data, size_t size, bool block)
{
    CHECK(address == 0x48 && block && (size == 4 || size == 8));
    memcpy(last_packet, data, size);
    last_size = size;
    sends++;
    return send_ok;
}
bool i2c_receive(i2c_address_t address, uint8_t *data, size_t size, bool block)
{
    CHECK(address == 0x48 && block && size == 4);
    receives++;
    if (!receive_ok)
        return false;
    for (unsigned i = 0; i < 4; i++)
        data[i] = (input_bits >> (8 * i)) & 0xFF;
    return true;
}
static xbar_t *claim(io_port_cfg_t *p, uint8_t *port, const char *desc, pin_cap_t caps)
{
    static xbar_t pin;
    CHECK(p && *port == 1 && desc && caps.irq_mode == IRQ_Mode_Change);
    if (!claim_ok)
        return NULL;
    *port = 5;
    return &pin;
}
io_port_cfg_t *ioports_cfg(io_port_cfg_t *p, io_port_type_t type, io_port_direction_t dir)
{
    CHECK(type == Port_Digital && dir == Port_Input);
    io_port_cfg_t cfg = {.n_ports = 2, .claim = claim};
    memcpy(p, &cfg, sizeof(cfg));
    return p;
}
bool ioport_enable_irq(uint8_t port, pin_irq_mode_t mode, ioport_interrupt_callback_ptr callback)
{
    CHECK(port == 5 && mode == IRQ_Mode_Change && callback);
    irq_handler = callback;
    return true;
}
bool ioports_add_digital(io_digital_t *ports)
{
    CHECK(ports && !bank.ports);
    bank = *ports;
    return true;
}
void ioport_save_input_settings(xbar_t *pin, gpio_in_config_t *cfg)
{
    CHECK(pin && cfg);
    saved++;
}
void ioport_save_output_settings(xbar_t *pin, gpio_out_config_t *cfg)
{
    CHECK(pin && cfg);
    saved++;
}
void system_raise_alarm(alarm_code_t alarm)
{
    CHECK(alarm == Alarm_ExpanderException);
    alarms++;
}
void report_warning(void *message)
{
    CHECK(message);
    warnings++;
}
bool task_add_immediate(foreground_task_ptr fn, void *data)
{
    CHECK(fn && pending < 64);
    tasks[pending].fn = fn;
    tasks[pending++].data = data;
    return true;
}
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    return task_add_immediate(fn, data);
}
void flex_run(void)
{
    unsigned guard = 0;
    while (pending)
    {
        CHECK(++guard < 100);
        foreground_task_ptr fn = tasks[0].fn;
        void *data = tasks[0].data;
        memmove(tasks, tasks + 1, --pending * sizeof(tasks[0]));
        fn(data);
    }
}
void flex_irq(uint32_t bits)
{
    CHECK(irq_handler);
    input_bits = bits;
    irq_handler(5, true);
    flex_run();
}
void flex_event(uint8_t port, bool state)
{
    events++;
    event_port = port;
    event_value = state;
}
static void reset(void) { chains++; }
static void options(bool newopt)
{
    (void)newopt;
    chains++;
}
void report_plugin(const char *name, const char *version)
{
    CHECK(strcmp(name, "FLEXGPIO") == 0 && strcmp(version, "0.04") == 0);
    chains++;
}
static void enumerate(bool low_level, pin_info_ptr fn, void *data)
{
    (void)low_level;
    chains++;
    xbar_t in = {.function = Input_Aux0 + 1, .group = PinGroup_AuxInput};
    fn(&in, data);
    xbar_t out = {.function = Output_Aux0 + 2, .group = PinGroup_AuxOutput};
    fn(&out, data);
}
static void delay(uint32_t ms, delay_callback_ptr callback)
{
    CHECK(ms == 50 && !callback);
    delay_calls++;
    if (inject_inputs)
    {
        inject_inputs = false;
        flex_irq(delay_bits);
    }
}
bool protocol_execute_realtime(void)
{
    realtime_calls++;
    if (abort_on_realtime)
        sys.abort = true;
    return !sys.abort;
}
void flex_prepare(void)
{
    hal.driver_reset = reset;
    hal.enumerate_pins = enumerate;
    hal.delay_ms = delay;
    grbl.on_report_options = options;
}
void flex_start(void)
{
    flex_prepare();
    flexgpio_init();
    CHECK(bank.ports);
    flex_run();
}
xbar_t flex_pin(io_port_direction_t dir, uint8_t port)
{
    xbar_t *pin = bank.get_pin_info(dir, port);
    CHECK(pin);
    return *pin;
}
