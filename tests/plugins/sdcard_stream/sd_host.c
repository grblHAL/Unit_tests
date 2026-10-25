#include "sd_host.h"
#if TEST_FATFS_STREAM
#include "fatfs_host.h"
#endif
system_t sys;
grbl_hal_t hal;
grbl_t grbl;
settings_t settings;
parser_state_t gc_state;
sys_state_t sd_state = STATE_IDLE;
unsigned sd_resets, sd_flushes, sd_changes, sd_statuses, sd_completions, sd_acks, sd_realtime,
    sd_feedback;
char sd_output[8192];
enqueue_realtime_command_ptr sd_rt_handler;
static sys_commands_t *commands;
static foreground_task_ptr tasks[8];
static void *task_data[8];
static unsigned task_count;
#if !TEST_FATFS_STREAM
static const embedded_file_t job = {.name = "job.nc", .size = 11, .data = "G1X1\nM30\nXX"};
static const embedded_file_t mixed = {.name = "mixed.ngc", .size = 10, .data = "A\r\nB\n\rC\rD\n"};
static const embedded_file_t binary = {.name = "readme.bin", .size = 3, .data = "BIN"};
static const embedded_file_t hidden = {
    .name = "hidden.nc", .size = 3, .st_mode = {.hidden = On}, .data = "M2\n"};
static const embedded_file_t macro = {.name = "P100.macro", .size = 3, .data = "M2\n"};
static const embedded_file_t *files[] = {&job, &mixed, &binary, &hidden, &macro, NULL};
#endif
static void output(const char *text)
{
    CHECK(strlen(sd_output) + strlen(text) < sizeof(sd_output));
    strcat(sd_output, text);
}
void sd_clear_output(void) { sd_output[0] = 0; }
int32_t sd_serial_read(void) { return SERIAL_NO_DATA; }
static bool realtime(uint8_t c)
{
    sd_realtime++;
    return c == CMD_STATUS_REPORT || c == CMD_CYCLE_START || c == CMD_TOOL_ACK;
}
static enqueue_realtime_command_ptr set_handler(enqueue_realtime_command_ptr handler)
{
    enqueue_realtime_command_ptr old = sd_rt_handler;
    sd_rt_handler = handler;
    return old;
}
static void flush(void) { sd_flushes++; }
static bool suspend_read(bool suspend)
{
    (void)suspend;
    return true;
}
static void reset(void) { sd_resets++; }
static void changed(void) { sd_changes++; }
static void completed(program_flow_t flow, bool check)
{
    (void)check;
    CHECK(flow == ProgramFlow_CompletedM30 || flow == ProgramFlow_CompletedM2 ||
          flow == ProgramFlow_Return);
    sd_completions++;
}
static void ack(void) { sd_acks++; }
static status_code_t status(status_code_t code)
{
    sd_statuses++;
    return code;
}
static message_code_t feedback(message_code_t message)
{
    sd_feedback++;
    return message;
}
void report_init_fns(void) { grbl.report.status_message = status; }
void report_message(const char *text, message_type_t type)
{
    (void)type;
    output(text);
}
void report_plugin(const char *name, const char *version)
{
    CHECK(name && version);
    output(name);
}
static void report_options(bool newopt) { (void)newopt; }
void errors_register(error_details_t *details) { CHECK(details && details->n_errors); }
void system_register_commands(sys_commands_t *value)
{
    CHECK(!commands);
    commands = value;
}
status_code_t sd_command(const char *name, char *args)
{
    CHECK(commands);
    for (unsigned i = 0; i < commands->n_commands; i++)
        if (!strcmp(name, commands->commands[i].command))
            return commands->commands[i].execute(sd_state, args);
    CHECK(false);
    return Status_Unhandled;
}
sys_state_t state_get(void) { return sd_state; }
void state_set(sys_state_t state) { sd_state = state; }
bool task_add_immediate(foreground_task_ptr fn, void *data)
{
    CHECK(task_count < 8);
    tasks[task_count] = fn;
    task_data[task_count++] = data;
    return true;
}
void sd_run_tasks(void)
{
    unsigned count = task_count;
    task_count = 0;
    for (unsigned i = 0; i < count; i++)
        tasks[i](task_data[i]);
}
void task_execute(bool systick) { CHECK(!systick); }
bool protocol_execute_realtime(void)
{
    CHECK(sd_state == STATE_CYCLE && (sys.rt_exec_state & EXEC_MOTION_CANCEL));
    sd_state = STATE_IDLE;
    return true;
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
static void set_bits(volatile uint_fast16_t *value, uint_fast16_t flag) { *value |= flag; }
void gc_filestream_changed(vfs_file_t *file) { CHECK(file == hal.stream.file); }
size_t gc_macro_get_pos(macro_id_t id, vfs_file_t *file)
{
#if TEST_FATFS_STREAM
    // This controller boundary reports no inline O-code definition in the active file.
    CHECK(id >= 100 && file == hal.stream.file);
#else
    CHECK(id == 100 && file == NULL);
#endif
    return 0;
}
void sd_mount(void)
{
#if TEST_FATFS_STREAM
    fatfs_prepare();
#else
    CHECK(fs_embedded_mount(files));
    vfs_drives_t *dh = vfs_drives_open();
    CHECK(dh);
    vfs_drive_t *drive;
    const vfs_t *backend = NULL;
    while ((drive = vfs_drives_read(dh, true)))
        if (!strcmp(drive->name, "embedded"))
            backend = drive->fs;
    vfs_drives_close(dh);
    CHECK(backend);
    CHECK(vfs_mount(NULL, "/", backend, (vfs_st_mode_t){.read_only = On}));
#endif
}
void sd_prepare(bool mount)
{
    hal.stream = (io_stream_t){.type = StreamType_Serial,
                               .read = sd_serial_read,
                               .write = output,
                               .reset_read_buffer = flush,
                               .set_enqueue_rt_handler = set_handler,
                               .suspend_read = suspend_read};
    hal.driver_reset = reset;
    hal.set_bits_atomic = set_bits;
    sd_rt_handler = realtime;
    grbl.on_stream_changed = changed;
    grbl.on_program_completed = completed;
    grbl.on_toolchange_ack = ack;
    grbl.on_report_options = report_options;
    grbl.report.status_message = status;
    grbl.report.feedback_message = feedback;
    fs_stream_init();
    if (mount)
        sd_mount();
}
void sd_read(char *buffer, size_t size)
{
    size_t n = 0;
    int32_t c;
    while ((c = hal.stream.read()) != SERIAL_NO_DATA)
    {
        CHECK(n + 1 < size);
        buffer[n++] = (char)c;
    }
    buffer[n] = 0;
}

bool ngc_call_pop(void)
{
    CHECK(false);
    return false;
}
bool protocol_enqueue_realtime_command(uint8_t c) { return realtime(c); }
void report_add_realtime(report_tracking_t report)
{
    (void)report;
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
status_code_t system_execute_line(char *line, stream_write_ptr write)
{
    (void)line;
    (void)write;
    CHECK(false);
    return Status_Unhandled;
}
report_tracking_flags_t report_get_rt_flags_all(void)
{
    CHECK(false);
    return (report_tracking_flags_t){0};
}
void report_realtime_status(stream_write_ptr write, status_report_tracking_t *report)
{
    (void)write;
    (void)report;
    CHECK(false);
}
void report_gcode_modes(stream_write_ptr write)
{
    (void)write;
    CHECK(false);
}
