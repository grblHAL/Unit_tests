#include "sd_controller_host.h"
grbl_t grbl;
settings_t settings;
system_t sys;
bool sd_detectable = true, sd_present = true;
unsigned sd_messages, sd_plugins, sd_options, sd_setups, sd_changes, sd_custom_mounts,
    sd_custom_unmounts;
char sd_output[256];
sdcard_events_t *sd_events;
static sys_commands_t *commands;
static foreground_task_ptr startup, immediate[4];
static void *startup_data, *immediate_data[4];
static unsigned immediate_count;
static FATFS custom_volume;
static void write_text(const char *text)
{
    CHECK(strlen(sd_output) + strlen(text) < sizeof(sd_output));
    strcat(sd_output, text);
}
static void previous_options(bool newopt)
{
    (void)newopt;
    sd_options++;
}
static void previous_report(stream_write_ptr write, report_tracking_flags_t report)
{
    (void)report;
    write("|previous");
}
static void previous_settings(settings_t *s, settings_changed_flags_t flags)
{
    CHECK(s == &settings);
    (void)flags;
    sd_changes++;
}
static bool setup(settings_t *s)
{
    CHECK(s == &settings);
    sd_setups++;
    grbl.on_settings_changed(s, (settings_changed_flags_t){0});
    return true;
}
static float detect_value(xbar_t *pin)
{
    CHECK(pin && pin->id == Input_SdCardDetect);
    return sd_present ? 0 : 1;
}
static void enumerate(bool low_level, pin_info_ptr callback, void *data)
{
    CHECK(!low_level && callback);
    static xbar_t pin;
    pin = (xbar_t){
        .id = Input_SdCardDetect, .function = Input_SdCardDetect, .get_value = detect_value};
    if (sd_detectable)
        callback(&pin, data);
}
void errors_register(error_details_t *details) { CHECK(details && details->n_errors == 2); }
void system_register_commands(sys_commands_t *value)
{
    CHECK(!commands && value);
    commands = value;
}
void report_plugin(const char *name, const char *version)
{
    CHECK(name && version);
    sd_plugins++;
}
void report_message(const char *text, message_type_t type)
{
    CHECK(text && type == Message_Info);
    sd_messages++;
    write_text(text);
}
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    CHECK(fn && !startup);
    startup = fn;
    startup_data = data;
    return true;
}
bool task_add_immediate(foreground_task_ptr fn, void *data)
{
    CHECK(fn && immediate_count < 4);
    immediate[immediate_count] = fn;
    immediate_data[immediate_count++] = data;
    return true;
}
void sd_startup(void)
{
    CHECK(startup);
    foreground_task_ptr fn = startup;
    startup = NULL;
    fn(startup_data);
}
void sd_run(void)
{
    unsigned count = immediate_count;
    immediate_count = 0;
    for (unsigned i = 0; i < count; i++)
        immediate[i](immediate_data[i]);
}
status_code_t sd_command(const char *name)
{
    CHECK(commands);
    for (unsigned i = 0; i < commands->n_commands; i++)
        if (!strcmp(commands->commands[i].command, name))
            return commands->commands[i].execute(STATE_IDLE, NULL);
    CHECK(false);
    return Status_Unhandled;
}
void sd_report(bool all)
{
    sd_output[0] = 0;
    grbl.on_realtime_report(write_text, (report_tracking_flags_t){.all = all});
}
void sd_prepare(void)
{
    fatfs_prepare_media();
    hal.enumerate_pins = enumerate;
    hal.driver_setup = setup;
    hal.stream.write = write_text;
    grbl.on_settings_changed = previous_settings;
    grbl.on_report_options = previous_options;
    grbl.on_realtime_report = previous_report;
    sd_events = sdcard_init();
    CHECK(sd_events && commands && hal.driver_cap.sd_card);
}
static char *custom_mount(FATFS **fs)
{
    sd_custom_mounts++;
    CHECK(f_mount(&custom_volume, "0:", 1) == FR_OK);
    *fs = &custom_volume;
    return "0:";
}
static bool custom_unmount(FATFS **fs)
{
    CHECK(*fs == &custom_volume);
    sd_custom_unmounts++;
    return f_unmount("0:") == FR_OK;
}
void sd_custom_events(void)
{
    sd_events->on_mount = custom_mount;
    sd_events->on_unmount = custom_unmount;
}
