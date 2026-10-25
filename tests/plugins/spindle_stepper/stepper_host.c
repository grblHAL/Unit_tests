#include "stepper_host.h"
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
settings_t settings;
parser_state_t gc_state;
setting_details_t *stepper_settings;
bool stepper_driver_ok = true, stepper_clock_ok = true, stepper_claimed;
unsigned stepper_pulses, stepper_forward, stepper_reverse, stepper_claims, stepper_warnings,
    stepper_saves, stepper_realtime, stepper_delays, stepper_previous_settings;
uint8_t stepper_enabled;
driver_settings_save_ptr stepper_save;
static uint64_t micros;
bool stepper_timer_available, stepper_timer_32bit = true, stepper_timer_claim_ok = true;
unsigned stepper_timer_claims, stepper_timer_starts, stepper_timer_stops, stepper_position_syncs;
uint32_t stepper_timer_period;
float stepper_resolution = 200;
static uint8_t timer_handle;
static timer_cfg_t timer_config;
static bool timer_pending;
static hal_timer_t timer_claim(timer_cap_t cap, uint32_t timebase)
{
    CHECK(!cap.periodic && timebase == 1000);
    CHECK(cap.resolution == Timer_32bit || cap.resolution == Timer_16bit);
    stepper_timer_claims++;
    return stepper_timer_claim_ok &&
                   cap.resolution == (stepper_timer_32bit ? Timer_32bit : Timer_16bit)
               ? &timer_handle
               : NULL;
}
static bool timer_configure(hal_timer_t timer, timer_cfg_t *cfg)
{
    CHECK(timer == &timer_handle && cfg && cfg->context && cfg->timeout_callback &&
          !cfg->single_shot);
    timer_config = *cfg;
    return true;
}
static bool timer_start(hal_timer_t timer, uint32_t period)
{
    CHECK(timer == &timer_handle && period > 0);
    CHECK(stepper_timer_32bit || period <= 65535);
    stepper_timer_period = period;
    timer_pending = true;
    stepper_timer_starts++;
    return true;
}
static bool timer_stop(hal_timer_t timer)
{
    CHECK(timer == &timer_handle);
    timer_pending = false;
    stepper_timer_stops++;
    return true;
}
static foreground_task_ptr delayed;
static void *delayed_data;
static uint64_t get_micros(void)
{
    micros += 10000;
    CHECK(micros < 1000000000ULL);
    return micros;
}
static void output_step(axes_signals_t step, axes_signals_t dir)
{
    CHECK(step.mask == 8 && (dir.mask == 0 || dir.mask == 8));
    stepper_pulses++;
    if (dir.mask)
        stepper_reverse++;
    else
        stepper_forward++;
}
static void enable(axes_signals_t axes, bool hold)
{
    CHECK(!hold);
    stepper_enabled = axes.mask;
}
static void claim(uint_fast8_t axis, bool value)
{
    CHECK(axis == 3);
    stepper_claimed = value;
    stepper_claims++;
}
static void realtime(uint_fast16_t state)
{
    CHECK(state == STATE_IDLE);
    stepper_realtime++;
}
static void delay(uint_fast16_t state)
{
    CHECK(state == STATE_IDLE);
    stepper_delays++;
}
static void previous_settings(settings_t *s, settings_changed_flags_t flags)
{
    CHECK(s == &settings);
    (void)flags;
    stepper_previous_settings++;
}
static void save(void) { stepper_saves++; }
driver_settings_save_ptr settings_claim_save(driver_settings_save_ptr fn)
{
    CHECK(fn);
    stepper_save = fn;
    return save;
}
bool settings_register(setting_details_t *d)
{
    CHECK(!stepper_settings);
    stepper_settings = d;
    return true;
}
void report_warning(void *message)
{
    CHECK(message);
    stepper_warnings++;
}
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    CHECK(fn == report_warning);
    fn(data);
    return true;
}
bool task_add_delayed(foreground_task_ptr fn, void *data, uint32_t ms)
{
    CHECK(fn && !delayed && ms == 2);
    delayed = fn;
    delayed_data = data;
    return true;
}
void task_delete(foreground_task_ptr fn, void *data)
{
    (void)fn;
    (void)data;
    CHECK(false);
}
void stepper_poll(unsigned count)
{
    CHECK(count < 10000);
    while (count--)
    {
        grbl.on_execute_realtime(STATE_IDLE);
        if (timer_pending)
        {
            timer_pending = false;
            micros += stepper_timer_period;
            timer_config.timeout_callback(timer_config.context);
        }
        if (delayed)
        {
            foreground_task_ptr fn = delayed;
            delayed = NULL;
            fn(delayed_data);
        }
    }
}
void stepper_cruise(spindle_ptrs_t *s)
{
    unsigned polls = 0;
    while (!s->get_state(s).at_speed)
    {
        CHECK(++polls < 2000);
        stepper_poll(1);
    }
}
void stepper_stop(spindle_ptrs_t *s)
{
    s->set_state(s, (spindle_state_t){0}, 0);
    unsigned polls = 0;
    do
    {
        CHECK(++polls < 2000);
        stepper_poll(1);
    } while (stepper_enabled & 8);
}
void stepper_prepare(void)
{
    for (unsigned i = 0; i < N_AXIS; i++)
        settings.axis[i].steps_per_mm = 80;
    settings.axis[3] = (axis_settings_t){
        .steps_per_mm = stepper_resolution, .max_rate = 600, .acceleration = 360000};
    settings.steppers.pulse_microseconds = 5;
    settings.spindle.at_speed_tolerance = 5;
    if (stepper_driver_ok)
        hal.stepper.output_step = output_step;
    if (stepper_clock_ok)
        hal.get_micros = get_micros;
    if (stepper_timer_available)
        hal.timer = (timer_ptrs_t){.claim = timer_claim,
                                   .configure = timer_configure,
                                   .start = timer_start,
                                   .stop = timer_stop};
    hal.stepper.enable = enable;
    hal.stepper.claim_motor = claim;
    grbl.on_execute_realtime = realtime;
    grbl.on_execute_delay = delay;
    grbl.on_settings_changed = previous_settings;
    stepper_spindle_init();
    if (stepper_settings)
    {
        stepper_settings->load();
        CHECK(spindle_select(0));
        grbl.on_settings_changed(&settings, (settings_changed_flags_t){.spindle = On});
    }
}
void plan_sync_position(void) { stepper_position_syncs++; }
void system_convert_array_steps_to_mpos(float *position, int32_t *steps)
{
    CHECK(steps == sys.position);
    for (unsigned i = 0; i < N_AXIS; i++)
        position[i] = steps[i] / settings.axis[i].steps_per_mm;
}
setting_id_t settings_get_axis_base(setting_id_t id, uint_fast8_t *idx)
{
    (void)id;
    (void)idx;
    CHECK(false);
    return Setting_SettingsMax;
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
void settings_write_global(void) { stepper_saves++; }
void report_add_realtime(report_tracking_t report) { (void)report; }
