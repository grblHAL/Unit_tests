#include "msp_host.h"
sys_state_t state_get(void) { return STATE_IDLE; }
void report_add_realtime(report_tracking_t report)
{
    (void)report;
    CHECK(false);
}
void report_realtime_status(stream_write_ptr write, status_report_tracking_t *report)
{
    (void)write;
    (void)report;
    CHECK(false);
}
void report_message(const char *text, message_type_t type)
{
    (void)text;
    (void)type;
    CHECK(false);
}
void report_gcode_modes(stream_write_ptr write)
{
    (void)write;
    CHECK(false);
}
report_tracking_flags_t report_get_rt_flags_all(void)
{
    CHECK(false);
    return (report_tracking_flags_t){0};
}
void gc_filestream_changed(vfs_file_t *file)
{
    (void)file;
    CHECK(false);
}
void task_execute(bool wait)
{
    (void)wait;
    CHECK(false);
}
bool task_add_immediate(foreground_task_ptr fn, void *data)
{
    (void)fn;
    (void)data;
    CHECK(false);
    return false;
}
bool task_add_delayed(foreground_task_ptr fn, void *data, uint32_t delay)
{
    (void)fn;
    (void)data;
    (void)delay;
    CHECK(false);
    return false;
}
void task_delete(foreground_task_ptr fn, void *data)
{
    (void)fn;
    (void)data;
    CHECK(false);
}
void system_register_commands(sys_commands_t *commands)
{
    (void)commands;
    CHECK(false);
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
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    (void)fn;
    (void)data;
    CHECK(false);
    return false;
}
