#include "coolant_host.h"
grbl_t grbl;
system_t sys;
settings_t settings;
setting_details_t *coolant_settings;
bool coolant_storage = true, coolant_signal = true;
int32_t coolant_temperature = 250;
coolant_state_t coolant_output;
unsigned coolant_warnings, coolant_writes, coolant_irqs, coolant_reports, coolant_plugins,
    coolant_prior_reports, coolant_reads;
uint32_t coolant_delay;
char coolant_text[256];
static xbar_t digital_pin[2], analog_pin[2];
unsigned coolant_inputs = 1, coolant_digital_port, coolant_analog_port, coolant_irq_physical;
bool coolant_restore_image, coolant_change_cap = true;
float coolant_wait_timeout;
static foreground_task_ptr delayed;
static void *delayed_data;
static ioport_interrupt_callback_ptr irq;
static uint8_t irq_port;
static ngc_named_param_get_ptr ok_param, temp_param;
static void write_text(const char *text)
{
    CHECK(strlen(coolant_text) + strlen(text) < sizeof(coolant_text));
    strcat(coolant_text, text);
}
static void set_state(coolant_state_t state)
{
    coolant_output = state;
    coolant_writes++;
}
static coolant_state_t get_state(void) { return coolant_output; }
static xbar_t *digital_info(io_port_direction_t dir, uint8_t port)
{
    return dir == Port_Input && port < coolant_inputs ? &digital_pin[port] : NULL;
}
static xbar_t *analog_info(io_port_direction_t dir, uint8_t port)
{
    return dir == Port_Input && port < coolant_inputs ? &analog_pin[port] : NULL;
}
static void digital_description(io_port_direction_t dir, uint8_t port, const char *text)
{
    CHECK(dir == Port_Input && port < coolant_inputs);
    digital_pin[port].description = text;
}
static void analog_description(io_port_direction_t dir, uint8_t port, const char *text)
{
    CHECK(dir == Port_Input && port < coolant_inputs);
    analog_pin[port].description = text;
}
static int32_t digital_wait(uint8_t port, wait_mode_t mode, float timeout)
{
    CHECK(port < coolant_inputs && (mode == WaitMode_Immediate || mode == WaitMode_High));
    CHECK(mode == WaitMode_High || timeout == 0);
    coolant_reads++;
    coolant_digital_port = port;
    coolant_wait_timeout = timeout;
    return coolant_signal;
}
static int32_t analog_wait(uint8_t port, wait_mode_t mode, float timeout)
{
    CHECK(port < coolant_inputs && mode == WaitMode_Immediate && timeout == 0);
    coolant_analog_port = port;
    return coolant_temperature;
}
static bool register_irq(uint8_t physical, uint8_t user, pin_irq_mode_t mode,
                         ioport_interrupt_callback_ptr handler)
{
    CHECK(physical < coolant_inputs && mode == IRQ_Mode_Falling && handler);
    coolant_irq_physical = physical;
    irq = handler;
    irq_port = user;
    coolant_irqs++;
    return true;
}
static uint_fast16_t atomic_set(volatile uint_fast16_t *value, uint_fast16_t bits)
{
    uint_fast16_t prior = *value;
    *value = bits;
    return prior;
}
static void previous_options(bool newopt)
{
    (void)newopt;
    coolant_prior_reports++;
}
static void previous_report(stream_write_ptr write, report_tracking_flags_t report)
{
    (void)report;
    write("|previous");
}
void coolant_prepare(bool inputs)
{
    prepare_eeprom();
    if (coolant_restore_image)
    {
        FILE *f = fopen("coolant-eeprom.bin", "rb");
        CHECK(f && fread(memory, 1, sizeof(memory), f) == sizeof(memory));
        CHECK(fgetc(f) == EOF && fclose(f) == 0);
    }
    CHECK(i2c_eeprom_init());
    hal.coolant = (coolant_ptrs_t){.set_state = set_state, .get_state = get_state};
    hal.set_value_atomic = atomic_set;
    hal.stream.write = write_text;
    grbl.on_report_options = previous_options;
    grbl.on_realtime_report = previous_report;
    if (inputs)
    {
        CHECK(coolant_inputs >= 1 && coolant_inputs <= 2);
        for (unsigned i = 0; i < coolant_inputs; i++)
        {
            digital_pin[i] = (xbar_t){.id = i, .function = Input_Aux0 + i, .cap.input = On};
            digital_pin[i].cap.irq_mode =
                IRQ_Mode_Falling | (coolant_change_cap ? IRQ_Mode_Change : 0);
            analog_pin[i] = (xbar_t){.id = i, .function = Input_Analog_Aux0 + i, .cap.input = On};
        }
        static io_ports_data_t d, a;
        static io_digital_t di;
        static io_analog_t ai;
        d.in.n_ports = a.in.n_ports = coolant_inputs;
        di = (io_digital_t){.ports = &d,
                            .get_pin_info = digital_info,
                            .set_pin_description = digital_description,
                            .wait_on_input = digital_wait,
                            .register_interrupt_handler = register_irq};
        ai = (io_analog_t){.ports = &a,
                           .get_pin_info = analog_info,
                           .set_pin_description = analog_description,
                           .wait_on_input = analog_wait};
        CHECK(ioports_add_digital(&di) && ioports_add_analog(&ai));
    }
    laser_coolant_init();
    if (coolant_settings && !coolant_restore_image)
        coolant_settings->restore();
}
void coolant_float(setting_id_t id, float value)
{
    CHECK(coolant_settings);
    for (unsigned i = 0; i < coolant_settings->n_settings; i++)
    {
        const setting_detail_t *d = &coolant_settings->settings[i];
        if (d->id == id)
        {
            CHECK(d->datatype == Format_Decimal && !d->get_value);
            *(float *)d->value = value;
            return;
        }
    }
    CHECK(false);
}
void coolant_load(void)
{
    CHECK(coolant_settings);
    coolant_settings->load();
}
nvs_address_t nvs_alloc(size_t size)
{
    CHECK(size && size < 256);
    return coolant_storage ? 2048 : 0;
}
bool settings_register(setting_details_t *d)
{
    CHECK(d);
    for (unsigned i = 0; i < d->n_settings; i++)
        if (d->settings[i].id == Setting_LaserCoolantOnDelay)
        {
            CHECK(!coolant_settings);
            coolant_settings = d;
        }
    return true;
}
bool ngc_virtual_ro_param_add(const char *name, ngc_named_param_get_ptr get)
{
    CHECK(name && get);
    if (!strcmp(name, "_laser_coolant_ok"))
    {
        CHECK(!ok_param);
        ok_param = get;
    }
    else
    {
        CHECK(!strcmp(name, "_laser_coolant_temp") && !temp_param);
        temp_param = get;
    }
    return true;
}
float coolant_param(const char *name)
{
    ngc_named_param_get_ptr get = !strcmp(name, "_laser_coolant_ok") ? ok_param : temp_param;
    CHECK(get);
    return get();
}
void report_warning(void *message)
{
    CHECK(message);
    coolant_warnings++;
}
void report_plugin(const char *name, const char *version)
{
    CHECK(name && version);
    coolant_plugins++;
}
void report_add_realtime(report_tracking_t report)
{
    CHECK(report == Report_Coolant);
    coolant_reports++;
}
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    CHECK(fn == report_warning);
    fn(data);
    return true;
}
bool task_add_delayed(foreground_task_ptr fn, void *data, uint32_t ms)
{
    CHECK(fn && !delayed);
    delayed = fn;
    delayed_data = data;
    coolant_delay = ms;
    return true;
}
void task_delete(foreground_task_ptr fn, void *data)
{
    if (delayed == fn && delayed_data == data)
    {
        delayed = NULL;
        coolant_delay = 0;
    }
}
void coolant_run_delayed(void)
{
    CHECK(delayed);
    foreground_task_ptr fn = delayed;
    delayed = NULL;
    fn(delayed_data);
}
void coolant_edge(bool state)
{
    CHECK(irq);
    coolant_signal = state;
    irq(irq_port, state);
}
bool protocol_execute_realtime(void)
{
    CHECK(false);
    return false;
}
bool protocol_exec_rt_system(void)
{
    CHECK(false);
    return false;
}
bool state_door_reopened(void)
{
    CHECK(false);
    return false;
}
void settings_write_global(void) { CHECK(false); }
void setting_remove_elements(setting_id_t id, uint32_t mask, bool trim)
{
    (void)id;
    (void)mask;
    (void)trim;
    CHECK(false);
}

static const setting_detail_t *port_detail(setting_id_t id)
{
    CHECK(coolant_settings);
    for (unsigned i = 0; i < coolant_settings->n_settings; i++)
        if (coolant_settings->settings[i].id == id)
            return &coolant_settings->settings[i];
    CHECK(false);
    return NULL;
}
status_code_t coolant_port(setting_id_t id, float value)
{
    const setting_detail_t *d = port_detail(id);
    CHECK(d->get_value);
    return ((setting_set_float_ptr)d->value)(id, value);
}
float coolant_get_port(setting_id_t id)
{
    const setting_detail_t *d = port_detail(id);
    return ((setting_get_float_ptr)d->get_value)(id);
}
bool coolant_has_param(const char *name)
{
    return !strcmp(name, "_laser_coolant_ok") ? ok_param != NULL : temp_param != NULL;
}
