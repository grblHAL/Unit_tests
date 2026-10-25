#include "offset_host.h"
grbl_t grbl;
system_t sys;
settings_t settings;
parser_state_t gc_state;
setting_details_t *offset_settings;
bool offset_storage = true, offset_accept = true;
unsigned offset_moves, offset_syncs, offset_planner_syncs, offset_wco, offset_previous,
    offset_reports, offset_plugins, offset_saves, offset_warnings;
float offset_target[N_AXIS];
static spindle_state_t states[3];
static void state(spindle_ptrs_t *s, spindle_state_t value, float rpm)
{
    (void)rpm;
    CHECK(s && s->id < 3);
    states[s->id] = value;
}
static spindle_state_t get_state(spindle_ptrs_t *s)
{
    CHECK(s && s->id < 3);
    return states[s->id];
}
static void previous_selected(spindle_ptrs_t *s)
{
    CHECK(s);
    offset_previous++;
}
static void previous_report(bool newopt)
{
    (void)newopt;
    offset_reports++;
}
void report_plugin(const char *name, const char *version)
{
    CHECK(name && version);
    offset_plugins++;
}
void offset_prepare(void)
{
    prepare_eeprom();
    CHECK(i2c_eeprom_init());
    settings.mode = Mode_Laser;
    for (unsigned i = 0; i < N_AXIS; i++)
    {
        settings.axis[i].steps_per_mm = 80;
        sys.position[i] = (int32_t)((i + 1) * 800);
    }
    grbl.on_spindle_selected = previous_selected;
    grbl.on_report_options = previous_report;
    static const spindle_ptrs_t primary = {.type = SpindleType_Basic,
                                           .ref_id = SPINDLE_ONOFF1,
                                           .set_state = state,
                                           .get_state = get_state};
    static const spindle_ptrs_t laser = {.type = SpindleType_Basic,
                                         .ref_id = SPINDLE_ONOFF1_DIR,
                                         .cap.laser = On,
                                         .set_state = state,
                                         .get_state = get_state};
    static const spindle_ptrs_t third = {.type = SpindleType_Basic,
                                         .ref_id = SPINDLE_ONOFF0,
                                         .set_state = state,
                                         .get_state = get_state};
    CHECK(spindle_register(&primary, "Primary") == 0 && spindle_register(&laser, "Laser") == 1 &&
          spindle_register(&third, "Other") == 2);
    spindle_offset_init();
    if (offset_settings)
        offset_settings->load();
    CHECK(spindle_select(0));
    sys.driver_started = On;
}
void offset_values(float x, float y)
{
    CHECK(offset_settings);
    for (unsigned i = 0; i < offset_settings->n_settings; i++)
    {
        const setting_detail_t *d = &offset_settings->settings[i];
        if (d->id == Setting_SpindleOffsetX)
            *(float *)d->value = x;
        if (d->id == Setting_SpindleOffsetY)
            *(float *)d->value = y;
    }
}
void offset_option(bool enabled)
{
    CHECK(offset_settings);
    for (unsigned i = 0; i < offset_settings->n_settings; i++)
    {
        const setting_detail_t *d = &offset_settings->settings[i];
        if (d->id == Setting_SpindleOffsetOptions)
        {
            CHECK(((setting_set_int_ptr)d->value)(d->id, enabled) == Status_OK);
            CHECK(((setting_get_int_ptr)d->get_value)(d->id) == enabled);
            return;
        }
    }
    CHECK(false);
}
void plan_data_init(plan_line_data_t *data) { memset(data, 0, sizeof(*data)); }
status_code_t mc_line(float *target, plan_line_data_t *data)
{
    CHECK(data && data->condition.rapid_motion);
    memcpy(offset_target, target, sizeof(offset_target));
    offset_moves++;
    if (!offset_accept)
        return Status_Aborted;
    for (unsigned i = 0; i < N_AXIS; i++)
        sys.position[i] = (int32_t)lroundf(target[i] * settings.axis[i].steps_per_mm);
    return Status_Handled;
}
void system_convert_array_steps_to_mpos(float *position, int32_t *steps)
{
    CHECK(steps == sys.position);
    for (unsigned i = 0; i < N_AXIS; i++)
        position[i] = steps[i] / settings.axis[i].steps_per_mm;
}
void plan_sync_position(void) { offset_planner_syncs++; }
void system_flag_wco_change(void) { offset_wco++; }
nvs_address_t nvs_alloc(size_t size)
{
    CHECK(size && size < 256);
    return offset_storage ? 2048 : 0;
}
bool settings_register(setting_details_t *details)
{
    CHECK(details);
    for (unsigned i = 0; i < details->n_settings; i++)
        if (details->settings[i].id == Setting_SpindleOffsetX)
        {
            CHECK(!offset_settings);
            offset_settings = details;
        }
    return true;
}
void report_warning(void *message)
{
    CHECK(message);
    offset_warnings++;
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
    offset_syncs++;
    return true;
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
void settings_write_global(void) { offset_saves++; }
