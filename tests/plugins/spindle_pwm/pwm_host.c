#include "pwm_host.h"
system_t sys;
grbl_t grbl;
settings_t settings;
setting_details_t *pwm_settings;
unsigned pwm_warnings, pwm_writes, pwm_ports;
bool pwm_storage = true, pwm_outputs[4];
static xbar_t pins[4], analog_pin;
bool pwm_analog_available = true, pwm_capable = true, pwm_config_ok = true;
unsigned pwm_config_calls, pwm_analog_calls;
float pwm_value;
pwm_config_t pwm_captured;
static bool analog_output(uint8_t port, float value)
{
    CHECK(port == 0);
    pwm_value = value;
    pwm_analog_calls++;
    return true;
}
static bool configure(xbar_t *pin, xbar_cfg_ptr_t data, bool persistent)
{
    CHECK(pin && data.pwm_config && !persistent);
    pwm_captured = *data.pwm_config;
    pwm_config_calls++;
    return pwm_config_ok;
}
static xbar_t *analog_info(io_port_direction_t dir, uint8_t port)
{
    return dir == Port_Output && port == 0 ? &analog_pin : NULL;
}
static void analog_description(io_port_direction_t dir, uint8_t port, const char *text)
{
    CHECK(dir == Port_Output && port == 0 && text);
    analog_pin.description = text;
}
static void previous_settings(settings_t *s, settings_changed_flags_t changed)
{
    (void)changed;
    CHECK(s == &settings);
}
static xbar_t *pin_info(io_port_direction_t dir, uint8_t port)
{
    return dir == Port_Output && port < pwm_ports ? &pins[port] : NULL;
}
static void description(io_port_direction_t dir, uint8_t port, const char *text)
{
    CHECK(dir == Port_Output && port < pwm_ports && text);
    pins[port].description = text;
}
static void digital(uint8_t port, bool on)
{
    CHECK(port < pwm_ports);
    pwm_outputs[port] = on;
    pwm_writes++;
}
void pwm_prepare(unsigned ports)
{
    CHECK(ports <= 4);
    pwm_ports = ports;
    prepare_eeprom();
    CHECK(i2c_eeprom_init());
    if (ports)
    {
        for (unsigned i = 0; i < ports; i++)
            pins[i] = (xbar_t){.id = i, .function = Output_Aux0 + i, .cap.output = On};
        static io_ports_data_t data;
        static io_digital_t io;
        data.out.n_ports = ports;
        io = (io_digital_t){.ports = &data,
                            .get_pin_info = pin_info,
                            .set_pin_description = description,
                            .digital_out = digital};
        CHECK(ioports_add_digital(&io));
    }
    if (pwm_analog_available)
    {
        analog_pin = (xbar_t){
            .id = 0, .function = Output_Analog_Aux0, .cap.output = On, .config = configure};
        analog_pin.cap.pwm = pwm_capable;
        static io_ports_data_t analog_data;
        static io_analog_t analog;
        analog_data.out.n_ports = 1;
        analog = (io_analog_t){.ports = &analog_data,
                               .get_pin_info = analog_info,
                               .set_pin_description = analog_description,
                               .analog_out = analog_output};
        CHECK(ioports_add_analog(&analog));
    }
    grbl.on_settings_changed = previous_settings;
    pwm_spindle_init();
}
void pwm_load(void)
{
    CHECK(pwm_settings);
    pwm_settings->load();
    pwm_settings->on_changed(&settings, (settings_changed_flags_t){.spindle = On});
}
nvs_address_t nvs_alloc(size_t size)
{
    CHECK(size && size < 256);
    return pwm_storage ? 2048 : 0;
}
bool settings_register(setting_details_t *details)
{
    CHECK(details);
    for (unsigned i = 0; i < details->n_settings; i++)
        if (details->settings[i].id == Setting_Spindle_OnPort)
        {
            CHECK(!pwm_settings);
            pwm_settings = details;
        }
    return true;
}
const setting_detail_t *pwm_detail(setting_id_t id)
{
    CHECK(pwm_settings);
    for (unsigned i = 0; i < pwm_settings->n_settings; i++)
        if (pwm_settings->settings[i].id == id)
            return &pwm_settings->settings[i];
    CHECK(false);
    return NULL;
}
status_code_t pwm_set(setting_id_t id, float value)
{
    const setting_detail_t *d = pwm_detail(id);
    return ((setting_set_float_ptr)d->value)(id, value);
}
float pwm_get(setting_id_t id)
{
    const setting_detail_t *d = pwm_detail(id);
    return ((setting_get_float_ptr)d->get_value)(id);
}
void report_warning(void *message)
{
    CHECK(message);
    pwm_warnings++;
}
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    CHECK(fn == report_warning);
    fn(data);
    return true;
}
void report_add_realtime(report_tracking_t report) { (void)report; }
bool settings_add_spindle_type(const char *name)
{
    CHECK(name);
    return true;
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
void st_rpm_changed(float rpm)
{
    (void)rpm;
    CHECK(false);
}
bool protocol_buffer_synchronize(void)
{
    CHECK(false);
    return false;
}
sys_state_t state_get(void) { return STATE_IDLE; }
const setting_detail_t *setting_get_details(setting_id_t id, setting_details_t **details)
{
    (void)id;
    (void)details;
    CHECK(false);
    return NULL;
}
uint32_t setting_get_int_value(const setting_detail_t *s, uint_fast16_t o)
{
    (void)s;
    (void)o;
    CHECK(false);
    return 0;
}
void gc_spindle_off(void)
{
    spindle_ptrs_t *s = spindle_get(0);
    if (s)
        s->set_state(s, (spindle_state_t){0}, 0);
}
void task_delete(foreground_task_ptr fn, void *data)
{
    (void)fn;
    (void)data;
    CHECK(false);
}
bool task_add_delayed(foreground_task_ptr fn, void *data, uint32_t ms)
{
    (void)fn;
    (void)data;
    (void)ms;
    CHECK(false);
    return false;
}
void system_raise_alarm(alarm_code_t alarm)
{
    (void)alarm;
    CHECK(false);
}
void setting_remove_elements(setting_id_t id, uint32_t mask, bool trim)
{
    (void)id;
    (void)mask;
    (void)trim;
    CHECK(id == Setting_SpindleInvertMask1 && trim);
}
void settings_write_global(void) { CHECK(false); }
