#include "onoff_host.h"
system_t sys;
grbl_t grbl;
settings_t settings;
setting_details_t *on_settings;
unsigned on_warnings, on_writes, on_ports;
bool on_storage = true, on_outputs[4];
static xbar_t pins[4];
static xbar_t *pin_info(io_port_direction_t dir, uint8_t port)
{
    return dir == Port_Output && port < on_ports ? &pins[port] : NULL;
}
static void description(io_port_direction_t dir, uint8_t port, const char *text)
{
    CHECK(dir == Port_Output && port < on_ports && text);
    pins[port].description = text;
}
static void digital(uint8_t port, bool on)
{
    CHECK(port < on_ports);
    on_outputs[port] = on;
    on_writes++;
}
void on_prepare(unsigned ports)
{
    CHECK(ports <= 4);
    on_ports = ports;
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
    onoff_spindle_init();
}
void on_load(void)
{
    CHECK(on_settings);
    on_settings->load();
}
nvs_address_t nvs_alloc(size_t size)
{
    CHECK(size && size < 256);
    return on_storage ? 2048 : 0;
}
bool settings_register(setting_details_t *details)
{
    CHECK(details);
    for (unsigned i = 0; i < details->n_settings; i++)
        if (details->settings[i].id == Setting_Spindle_OnPort)
        {
            CHECK(!on_settings);
            on_settings = details;
        }
    return true;
}
static const setting_detail_t *detail(setting_id_t id)
{
    CHECK(on_settings);
    for (unsigned i = 0; i < on_settings->n_settings; i++)
        if (on_settings->settings[i].id == id)
            return &on_settings->settings[i];
    CHECK(false);
    return NULL;
}
status_code_t on_set(setting_id_t id, float value)
{
    const setting_detail_t *d = detail(id);
    return ((setting_set_float_ptr)d->value)(id, value);
}
float on_get(setting_id_t id)
{
    const setting_detail_t *d = detail(id);
    return ((setting_get_float_ptr)d->get_value)(id);
}
void report_warning(void *message)
{
    CHECK(message);
    on_warnings++;
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
    CHECK(false);
}
void settings_write_global(void) { CHECK(false); }
