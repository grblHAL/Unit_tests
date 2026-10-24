#include "atci_host.h"
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
setting_details_t *registered_settings;
float position[N_AXIS];
bool gpio[8] = {true, true, true, true, true, true, true, true}, alloc_ok = true,
     previous_accept = true;
unsigned check_calls, clip_calls, chains, saves, messages;
char output[512], message[192];
uint32_t delay_ms;
static foreground_task_ptr delayed;
static void *delayed_data;
static uint8_t nvs[64];
static size_t stored;
int atci_digital_in(unsigned port, unsigned pin)
{
    CHECK(port == 0 && pin < 8);
    return gpio[pin];
}
float *plan_get_position(void) { return position; }
nvs_address_t nvs_alloc(size_t size)
{
    CHECK(size <= sizeof(nvs));
    return alloc_ok ? 2048 : 0;
}
static nvs_transfer_result_t read_nvs(uint8_t *dst, uint32_t addr, uint32_t size, bool checksum)
{
    CHECK(addr == 2048 && checksum && size <= sizeof(nvs));
    if (!stored)
        return false;
    CHECK(size == stored);
    memcpy(dst, nvs, size);
    return true;
}
static nvs_transfer_result_t write_nvs(uint32_t addr, uint8_t *src, uint32_t size, bool checksum)
{
    CHECK(addr == 2048 && checksum && size <= sizeof(nvs));
    memcpy(nvs, src, size);
    stored = size;
    saves++;
    return true;
}
bool settings_register(setting_details_t *details)
{
    CHECK(!registered_settings);
    registered_settings = details;
    return true;
}
bool task_add_delayed(foreground_task_ptr fn, void *data, uint32_t ms)
{
    CHECK(fn && !delayed);
    delayed = fn;
    delayed_data = data;
    delay_ms = ms;
    return true;
}
static void write_text(const char *text)
{
    CHECK(strlen(output) + strlen(text) < sizeof(output));
    strcat(output, text);
}
void report_message(const char *text, message_type_t type)
{
    CHECK(type == Message_Info || type == Message_Warning);
    CHECK(strlen(text) < sizeof(message));
    strcpy(message, text);
    messages++;
}
void report_plugin(const char *name, const char *version)
{
    CHECK(strcmp(name, "SIENCI ATCi plugin") == 0 && strcmp(version, "0.5.0") == 0);
    chains++;
}
static bool previous_check(float *target, axes_signals_t axes, bool cartesian,
                           work_envelope_t *envelope)
{
    CHECK(target && axes.mask == 7 && cartesian && !envelope);
    check_calls++;
    return previous_accept;
}
static void previous_clip(float *target, float *current, work_envelope_t *envelope)
{
    CHECK(target && current == position && !envelope);
    clip_calls++;
}
static void options(bool newopt)
{
    (void)newopt;
    chains++;
}
static void report(stream_write_ptr fn, report_tracking_flags_t flags)
{
    (void)flags;
    fn("|previous");
    chains++;
}
static void ngc(void) { chains++; }
static void tool(tool_data_t *t)
{
    CHECK(t);
    chains++;
}
static user_mcode_type_t check_mcode(user_mcode_t code)
{
    CHECK(code != 960);
    chains++;
    return UserMCode_Normal;
}
static status_code_t validate_mcode(parser_block_t *block)
{
    CHECK(block->user_mcode != 960);
    chains++;
    return Status_SettingDisabled;
}
static void execute_mcode(sys_state_t state, parser_block_t *block)
{
    (void)state;
    CHECK(block->user_mcode != 960);
    chains++;
}
void atci_prepare(void)
{
    hal.nvs.memcpy_from_nvs = read_nvs;
    hal.nvs.memcpy_to_nvs = write_nvs;
    hal.stream.write = write_text;
    grbl.check_travel_limits = previous_check;
    grbl.apply_travel_limits = previous_clip;
    grbl.on_report_options = options;
    grbl.on_realtime_report = report;
    grbl.on_report_ngc_parameters = ngc;
    grbl.on_tool_selected = tool;
    grbl.on_tool_changed = tool;
    grbl.user_mcode = (user_mcode_ptrs_t){
        .check = check_mcode, .validate = validate_mcode, .execute = execute_mcode};
}
void atci_start(void)
{
    atci_prepare();
    atci_init();
    CHECK(registered_settings && registered_settings->n_settings == 5);
    registered_settings->load();
    CHECK(delay_ms == 1000);
}
void atci_flags(uint8_t value)
{
    const setting_detail_t *s = registered_settings->settings;
    CHECK(s->id == 683 && s->datatype == Format_XBitfield);
    *(uint8_t *)s->value = value;
    registered_settings->save();
}
void atci_bounds(float xmin, float ymin, float xmax, float ymax)
{
    float values[] = {xmin, ymin, xmax, ymax};
    for (unsigned i = 0; i < 4; i++)
    {
        const setting_detail_t *s = &registered_settings->settings[i + 1];
        CHECK(s->datatype == Format_Decimal);
        *(float *)s->value = values[i];
    }
    registered_settings->save();
}
bool atci_check(float x, float y)
{
    float target[N_AXIS] = {x, y, 0};
    axes_signals_t axes = {.mask = 7};
    return grbl.check_travel_limits(target, axes, true, NULL);
}
void atci_clip(float *target) { grbl.apply_travel_limits(target, position, NULL); }
status_code_t atci_command(float value, sys_state_t state)
{
    parser_block_t block = {0};
    block.user_mcode = (user_mcode_t)960;
    block.words.p = 1;
    block.values.p = value;
    CHECK(grbl.user_mcode.check(block.user_mcode) == UserMCode_Normal);
    parameter_words_t supplied = block.words;
    status_code_t result = grbl.user_mcode.validate(&block);
    if (result == Status_OK)
    {
        // CORE gcode.c restores the words consumed by validation for execution.
        block.words.mask = supplied.mask ^ block.words.mask;
        grbl.user_mcode.execute(state, &block);
    }
    return result;
}
void atci_poll(void)
{
    CHECK(delayed);
    foreground_task_ptr fn = delayed;
    void *data = delayed_data;
    delayed = NULL;
    fn(data);
    CHECK(delay_ms == 100);
}
void atci_report(void)
{
    output[0] = 0;
    grbl.on_realtime_report(write_text, (report_tracking_flags_t){0});
}
