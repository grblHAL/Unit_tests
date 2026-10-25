#include "mpg_host.h"
#include "grbl/gcode.h"
parser_state_t gc_state;
sys_state_t core_state = STATE_IDLE;
unsigned status_reports, mode_reports, command_calls;
status_code_t command_status = Status_OK;
char last_command[32], command_history[8][32];
status_code_t system_execute_line(char *line, stream_write_ptr write)
{
    CHECK(line && write && strlen(line) < sizeof(last_command));
    strcpy(last_command, line);
    CHECK(command_calls < 8);
    strcpy(command_history[command_calls++], line);
    write("[host-command]" ASCII_EOL);
    return command_status;
}
static struct
{
    foreground_task_ptr fn;
    void *data;
    uint32_t due;
} tasks[32];
static unsigned pending;
sys_state_t state_get(void) { return core_state; }
void report_add_realtime(report_tracking_t report)
{
    CHECK(report == Report_MPGMode);
    mode_reports++;
}
void report_realtime_status(stream_write_ptr write, status_report_tracking_t *report)
{
    CHECK(write && report);
    status_reports++;
    write("<host-status>\n");
}
void report_gcode_modes(stream_write_ptr write)
{
    CHECK(write);
    write("[host-modes]\n");
}
report_tracking_flags_t report_get_rt_flags_all(void)
{
    return (report_tracking_flags_t){.value = 0};
}
void report_message(const char *text, message_type_t type)
{
    (void)text;
    (void)type;
    CHECK(false);
}
void gc_filestream_changed(vfs_file_t *file)
{
    (void)file;
    CHECK(false);
}
bool task_add_delayed(foreground_task_ptr fn, void *data, uint32_t delay)
{
    CHECK(fn && pending < 32);
    tasks[pending].fn = fn;
    tasks[pending].data = data;
    tasks[pending++].due = now + delay;
    return true;
}
bool task_add_immediate(foreground_task_ptr fn, void *data)
{
    return task_add_delayed(fn, data, 0);
}
void mpg_core_run(void)
{
    unsigned guard = 0;
    for (;;)
    {
        unsigned next = pending;
        for (unsigned i = 0; i < pending; i++)
            if (tasks[i].due <= now)
            {
                next = i;
                break;
            }
        if (next == pending)
            return;
        CHECK(++guard < 64);
        foreground_task_ptr fn = tasks[next].fn;
        void *data = tasks[next].data;
        pending--;
        memmove(tasks + next, tasks + next + 1, (pending - next) * sizeof(tasks[0]));
        fn(data);
    }
}
void task_execute(bool wait)
{
    CHECK(!wait);
    mpg_core_run();
}
void task_delete(foreground_task_ptr fn, void *data)
{
    (void)fn;
    (void)data;
    CHECK(false);
}
bool ioports_enumerate(io_port_type_t type, io_port_direction_t dir, pin_cap_t filter,
                       ioports_enumerate_callback_ptr callback, void *data)
{
    (void)type;
    (void)dir;
    (void)filter;
    (void)callback;
    (void)data;
    CHECK(false);
    return false;
}
bool ioport_digital_out(uint8_t port, uint32_t value)
{
    (void)port;
    (void)value;
    CHECK(false);
    return false;
}
