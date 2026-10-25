#include "clone_host.h"
grbl_t grbl;
system_t sys;
settings_t settings;
setting_details_t *clone_settings;
bool clone_storage = true;
unsigned clone_calls, clone_selected, clone_warnings;
spindle_state_t clone_output;
float clone_rpm;
uint_fast16_t clone_pwm;
static spindle_pwm_t base_pwm;
static foreground_task_ptr tasks[4];
static void *task_data[4];
static unsigned task_count;
static spindle_state_t base_state;
static uint_fast16_t get_pwm(spindle_ptrs_t *s, float rpm)
{
    CHECK(s && s->context.pwm && s->context.pwm->compute_value);
    return s->context.pwm->compute_value(s->context.pwm, rpm, false);
}
static void update_pwm(spindle_ptrs_t *s, uint_fast16_t value)
{
    CHECK(s);
    clone_pwm = value;
}
static void set_state(spindle_ptrs_t *s, spindle_state_t state, float rpm)
{
    CHECK(s);
    clone_output = base_state = state;
    clone_rpm = rpm;
    clone_calls++;
    update_pwm(s, get_pwm(s, rpm));
}
static spindle_state_t get_state(spindle_ptrs_t *s)
{
    CHECK(s);
    return base_state;
}
static bool configure(spindle_ptrs_t *s)
{
    return spindle_precompute_pwm_values(s, &base_pwm, &settings.pwm_spindle, 1000000);
}
static void previous_selected(spindle_ptrs_t *s)
{
    CHECK(s);
    clone_selected++;
}
static void previous_settings(settings_t *s, settings_changed_flags_t flags)
{
    CHECK(s == &settings);
    (void)flags;
}
void clone_prepare(void)
{
    prepare_eeprom();
    CHECK(i2c_eeprom_init());
    settings.mode = Mode_Standard;
    settings.pwm_spindle = (spindle_pwm_settings_t){
        .rpm_min = 0, .rpm_max = 10000, .pwm_freq = 1000, .pwm_max_value = 100};
    grbl.on_spindle_selected = previous_selected;
    grbl.on_settings_changed = previous_settings;
    if (TEST_REJECT != 1)
    {
        static spindle_ptrs_t driver;
        driver = (spindle_ptrs_t){.type = SpindleType_PWM,
                                  .ref_id = SPINDLE_PWM0,
                                  .cap.direction = On,
                                  .config = configure,
                                  .set_state = set_state,
                                  .get_state = get_state,
                                  .get_pwm = get_pwm,
                                  .update_pwm = update_pwm};
#if TEST_REJECT == 2
        driver.cap.direction = Off;
#elif TEST_REJECT == 3
        driver.update_pwm = NULL;
#endif
        CHECK(configure(&driver));
        CHECK(spindle_register(&driver, "Driver PWM") == 0);
    }
    cloned_spindle_init();
    if (clone_settings)
        clone_settings->load();
    unsigned count = task_count;
    task_count = 0;
    for (unsigned i = 0; i < count; i++)
        tasks[i](task_data[i]);
}
void clone_float(setting_id_t id, float value)
{
    CHECK(clone_settings);
    for (unsigned i = 0; i < clone_settings->n_settings; i++)
    {
        const setting_detail_t *d = &clone_settings->settings[i];
        if (d->id == id)
        {
            CHECK(d->datatype == Format_Decimal && !d->get_value);
            *(float *)d->value = value;
            return;
        }
    }
    CHECK(false);
}
nvs_address_t nvs_alloc(size_t size)
{
    CHECK(size && size < 256);
    return clone_storage ? 2048 : 0;
}
bool settings_register(setting_details_t *details)
{
    CHECK(details);
    for (unsigned i = 0; i < details->n_settings; i++)
        if (details->settings[i].id == Setting_Spindle_OnPort)
        {
            CHECK(!clone_settings);
            clone_settings = details;
        }
    return true;
}
void report_warning(void *message)
{
    CHECK(message);
    clone_warnings++;
}
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    CHECK(fn && task_count < 4);
    tasks[task_count] = fn;
    task_data[task_count++] = data;
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
