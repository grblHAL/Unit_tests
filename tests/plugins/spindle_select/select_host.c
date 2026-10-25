#include "select_host.h"
#include <string.h>
grbl_t grbl;
system_t sys;
settings_t settings;
setting_details_t *select_settings;
bool select_storage = true, select_setup_ok = true, select_load_image;
unsigned select_warnings, select_previous_tools, select_previous_checks, select_previous_validates,
    select_previous_executes;
char select_output[256];
static spindle_state_t states[2];
static foreground_task_ptr pending;
static void *pending_data;
static const setting_detail_t primary_setting = {.id = Setting_SpindleType,
                                                 .format = "Primary,Secondary"};
static void state(spindle_ptrs_t *s, spindle_state_t value, float rpm)
{
    (void)rpm;
    CHECK(s && s->id < 2);
    states[s->id] = value;
}
static spindle_state_t get_state(spindle_ptrs_t *s)
{
    CHECK(s && s->id < 2);
    return states[s->id];
}
static bool setup(settings_t *s)
{
    CHECK(s == &settings);
    return select_setup_ok;
}
static void output(const char *s)
{
    CHECK(strlen(select_output) + strlen(s) < sizeof(select_output));
    strcat(select_output, s);
}
static void options(bool newopt) { (void)newopt; }
static void selected(tool_data_t *tool)
{
    CHECK(tool);
    select_previous_tools++;
}
static user_mcode_type_t previous_check(user_mcode_t code)
{
    (void)code;
    select_previous_checks++;
    return UserMCode_Unsupported;
}
static status_code_t previous_validate(parser_block_t *b)
{
    CHECK(b);
    select_previous_validates++;
    return Status_Unhandled;
}
static void previous_execute(sys_state_t s, parser_block_t *b)
{
    CHECK(s == STATE_IDLE && b);
    select_previous_executes++;
}
nvs_address_t nvs_alloc(size_t size)
{
    CHECK(size && size < 256);
    return select_storage ? 2048 : 0;
}
bool settings_register(setting_details_t *d)
{
    CHECK(!select_settings);
    select_settings = d;
    return true;
}
const setting_detail_t *setting_get_details(setting_id_t id, setting_details_t **d)
{
    if (d)
        *d = select_settings;
    if (id == Setting_SpindleType)
        return &primary_setting;
    if (select_settings)
        for (unsigned i = 0; i < select_settings->n_settings; i++)
            if (select_settings->settings[i].id == Setting_SpindleEnableBase &&
                id >= Setting_SpindleEnableBase && id <= Setting_SpindleEnable7)
                return &select_settings->settings[i];
    return NULL;
}
uint32_t setting_get_int_value(const setting_detail_t *d, uint_fast16_t offset)
{
    CHECK(d);
    if (d == &primary_setting)
        return 0;
    return ((setting_get_int_ptr)d->get_value)(d->id + offset);
}
static const setting_detail_t *detail(setting_id_t base)
{
    CHECK(select_settings);
    for (unsigned i = 0; i < select_settings->n_settings; i++)
        if (select_settings->settings[i].id == base)
            return &select_settings->settings[i];
    CHECK(false);
    return NULL;
}
status_code_t select_binding(unsigned slot, unsigned value)
{
    const setting_detail_t *d = detail(Setting_SpindleEnableBase);
    return ((setting_set_int_ptr)d->value)(d->id + slot, value);
}
status_code_t select_tool_start(unsigned slot, unsigned value)
{
    const setting_detail_t *d = detail(Setting_SpindleToolStartBase);
    return ((setting_set_int_ptr)d->value)(d->id + slot, value);
}
status_code_t select_command(bool p, float value, bool execute)
{
    parser_block_t block = {0};
    block.user_mcode = Spindle_Select;
    block.words.p = p;
    block.words.q = !p;
    if (p)
        block.values.p = value;
    else
        block.values.q = value;
    parameter_words_t supplied = block.words;
    status_code_t result = grbl.user_mcode.validate(&block);
    if (result == Status_OK && execute)
    {
        block.words.mask = supplied.mask ^ block.words.mask;
        CHECK(block.user_mcode_sync);
        grbl.user_mcode.execute(STATE_IDLE, &block);
    }
    return result;
}
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    CHECK(!pending);
    pending = fn;
    pending_data = data;
    return true;
}
void report_warning(void *message)
{
    CHECK(message);
    select_warnings++;
}
void select_prepare(void)
{
    prepare_eeprom();
    if (select_load_image)
    {
        FILE *f = fopen("select-eeprom.bin", "rb");
        CHECK(f && fread(memory, 1, sizeof(memory), f) == sizeof(memory));
        CHECK(fgetc(f) == EOF && fclose(f) == 0);
    }
    CHECK(i2c_eeprom_init());
    hal.driver_setup = setup;
    hal.stream.write = output;
    grbl.on_report_options = options;
    grbl.on_tool_selected = selected;
    grbl.user_mcode = (user_mcode_ptrs_t){
        .check = previous_check, .validate = previous_validate, .execute = previous_execute};
    static const spindle_ptrs_t primary = {.type = SpindleType_Basic,
                                           .ref_id = SPINDLE_ONOFF1,
                                           .set_state = state,
                                           .get_state = get_state};
    static const spindle_ptrs_t secondary = {.type = SpindleType_Basic,
                                             .ref_id = SPINDLE_ONOFF1_DIR,
                                             .cap.direction = On,
                                             .set_state = state,
                                             .get_state = get_state};
    CHECK(spindle_register(&primary, "Primary") == 0 &&
          spindle_register(&secondary, "Secondary") == 1);
    spindle_select_init();
    if (select_settings)
    {
        select_settings->load();
        CHECK(hal.driver_setup(&settings) == select_setup_ok);
    }
    if (pending)
    {
        foreground_task_ptr fn = pending;
        pending = NULL;
        fn(pending_data);
    }
}
bool settings_add_spindle_type(const char *name)
{
    CHECK(name);
    return true;
}
void report_add_realtime(report_tracking_t report) { (void)report; }
void gc_spindle_off(void)
{
    spindle_ptrs_t *s = spindle_get(0);
    if (s)
        s->set_state(s, (spindle_state_t){0}, 0);
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
bool protocol_buffer_synchronize(void)
{
    CHECK(false);
    return false;
}
void st_rpm_changed(float rpm)
{
    (void)rpm;
    CHECK(false);
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
sys_state_t state_get(void) { return STATE_IDLE; }
