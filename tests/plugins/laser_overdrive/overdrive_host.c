#include "overdrive_host.h"
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
settings_t settings;
bool ovd_initial_select = true;
unsigned ovd_resets, ovd_completions, ovd_selected, ovd_settings, ovd_reports, ovd_plugins,
    ovd_checks, ovd_validates, ovd_executes;
static spindle_ptrs_t driver;
static spindle_pwm_t pwm;
static spindle_state_t state;
static void update_pwm(spindle_ptrs_t *s, uint_fast16_t value)
{
    CHECK(s);
    (void)value;
}
static uint_fast16_t get_pwm(spindle_ptrs_t *s, float rpm)
{
    CHECK(s && s->context.pwm);
    return s->context.pwm->compute_value(s->context.pwm, rpm, false);
}
static void set_state(spindle_ptrs_t *s, spindle_state_t value, float rpm)
{
    CHECK(s);
    (void)rpm;
    state = value;
}
static spindle_state_t get_state(spindle_ptrs_t *s)
{
    CHECK(s);
    return state;
}
static bool configure(spindle_ptrs_t *s)
{
    bool ok = spindle_precompute_pwm_values(s, &pwm, &settings.pwm_spindle, 1000000);
    spindle_update_caps(s, &pwm);
    return ok;
}
static void reset(void) { ovd_resets++; }
static void completed(program_flow_t flow, bool check)
{
    CHECK(flow == ProgramFlow_CompletedM2 || flow == ProgramFlow_CompletedM30);
    (void)check;
    ovd_completions++;
}
static void selected(spindle_ptrs_t *s)
{
    CHECK(s);
    ovd_selected++;
}
static void changed(settings_t *s, settings_changed_flags_t flags)
{
    CHECK(s == &settings);
    (void)flags;
    CHECK(configure(&driver));
    ovd_settings++;
}
static void report(bool newopt)
{
    (void)newopt;
    ovd_reports++;
}
static user_mcode_type_t previous_check(user_mcode_t code)
{
    (void)code;
    ovd_checks++;
    return UserMCode_Unsupported;
}
static status_code_t previous_validate(parser_block_t *b)
{
    CHECK(b);
    ovd_validates++;
    return Status_Unhandled;
}
static void previous_execute(sys_state_t s, parser_block_t *b)
{
    CHECK(s == STATE_IDLE && b);
    ovd_executes++;
}
void report_plugin(const char *name, const char *version)
{
    CHECK(name && version);
    ovd_plugins++;
}
nvs_address_t nvs_alloc(size_t size)
{
    (void)size;
    CHECK(false);
    return 0;
}
bool settings_register(setting_details_t *d)
{
    (void)d;
    CHECK(false);
    return false;
}
void report_warning(void *message)
{
    (void)message;
    CHECK(false);
}
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    (void)fn;
    (void)data;
    CHECK(false);
    return false;
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
void ovd_prepare(void)
{
    settings.mode = Mode_Laser;
    settings.pwm_spindle = (spindle_pwm_settings_t){.rpm_min = 0,
                                                    .rpm_max = 10000,
                                                    .pwm_freq = 1000,
                                                    .pwm_max_value = 100,
                                                    .flags.enable_rpm_controlled = On};
    hal.driver_reset = reset;
    grbl.on_program_completed = completed;
    grbl.on_spindle_selected = selected;
    grbl.on_settings_changed = changed;
    grbl.on_report_options = report;
    grbl.user_mcode = (user_mcode_ptrs_t){
        .check = previous_check, .validate = previous_validate, .execute = previous_execute};
    driver = (spindle_ptrs_t){.type = SpindleType_PWM,
                              .ref_id = SPINDLE_PWM0,
                              .config = configure,
                              .set_state = set_state,
                              .get_state = get_state,
                              .get_pwm = get_pwm,
                              .update_pwm = update_pwm};
    CHECK(configure(&driver));
    CHECK(spindle_register(&driver, "Laser PWM") == 0);
    static const spindle_ptrs_t basic = {.type = SpindleType_Basic,
                                         .ref_id = SPINDLE_ONOFF1,
                                         .set_state = set_state,
                                         .get_state = get_state};
    CHECK(spindle_register(&basic, "Basic spindle") == 1);
    laser_ovd_init();
    if (ovd_initial_select)
        CHECK(spindle_select(0));
}
status_code_t ovd_command(float percent, bool execute)
{
    CHECK(grbl.user_mcode.check(Laser_Overdrive) == UserMCode_Normal);
    parser_block_t block = {.user_mcode = Laser_Overdrive, .words.p = On, .values.p = percent};
    parameter_words_t supplied = block.words;
    status_code_t status = grbl.user_mcode.validate(&block);
    if (status == Status_OK && execute)
    {
        block.words.mask = supplied.mask ^ block.words.mask;
        grbl.user_mcode.execute(STATE_IDLE, &block);
    }
    return status;
}
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
void report_add_realtime(report_tracking_t report) { (void)report; }
