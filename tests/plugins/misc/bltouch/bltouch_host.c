#include "bltouch_host.h"
#include <string.h>
#include <stdio.h>
grbl_hal_t hal;
grbl_t grbl;
settings_t settings;
system_t sys;
bool claims_ok = true, probe_ok = true, native_probe;
float angle, last_delay;
unsigned outputs, delays, resets, starts, completed, selections, warnings;
probe_id_t selected_probe;
uint32_t delayed_ms;
foreground_task_ptr delayed_task;
static foreground_task_ptr startup, immediate;
static void *startup_data, *immediate_data, *delayed_data;
static sys_commands_t *commands;
static float read_angle(xbar_t *pin)
{
    CHECK(pin->id == 0);
    return angle;
}
bool ioports_enumerate(io_port_type_t type, io_port_direction_t dir, pin_cap_t caps,
                       ioports_enumerate_callback_ptr callback, void *data)
{
    CHECK(type == Port_Analog && dir == Port_Output && caps.servo_pwm && caps.claimable);
    xbar_t servo = {.id = 0, .get_value = read_angle};
    return callback(&servo, 4, data);
}
xbar_t *ioport_claim(io_port_type_t type, io_port_direction_t dir, uint8_t *port,
                     const char *description)
{
    static xbar_t servo;
    CHECK(type == Port_Analog && dir == Port_Output && *port == 4 &&
          strcmp(description, "BLTouch probe") == 0);
    if (!claims_ok)
        return NULL;
    *port = 2;
    return &servo;
}
bool ioport_analog_out(uint8_t port, float value)
{
    CHECK(port == 2);
    last_delay = 0;
    angle = value;
    outputs++;
    return true;
}
static void delay_ms(uint32_t ms, void (*callback)(void))
{
    CHECK(ms == DWELL_TIME_STEP && callback == NULL && delays < 200);
    last_delay += (float)ms / 1000.0f;
    delays++;
}
bool protocol_execute_realtime(void)
{
    CHECK(false);
    return false;
}
bool protocol_exec_rt_system(void) { return true; }
bool state_door_reopened(void) { return false; }
static void write_text(const char *text) { CHECK(text); }
static void reset(void) { resets++; }
static bool probe_start(axes_signals_t axes, float *target, plan_line_data_t *data)
{
    CHECK(axes.mask && target && data);
    starts++;
    return probe_ok;
}
static void probe_completed(void) { completed++; }
static bool select_probe(probe_id_t id)
{
    selected_probe = id;
    selections++;
    return true;
}
static void options(bool newopt) { (void)newopt; }
void report_plugin(const char *name, const char *version)
{
    CHECK(name && strcmp(version, "0.06") == 0);
}
void report_warning(void *message)
{
    CHECK(message);
    warnings++;
}
void system_register_commands(sys_commands_t *list)
{
    CHECK(!commands && list->n_commands == 2);
    commands = list;
}
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    CHECK(!startup);
    startup = fn;
    startup_data = data;
    return true;
}
bool task_add_immediate(foreground_task_ptr fn, void *data)
{
    CHECK(!immediate);
    immediate = fn;
    immediate_data = data;
    return true;
}
bool task_add_delayed(foreground_task_ptr fn, void *data, uint32_t ms)
{
    CHECK(!delayed_task);
    delayed_task = fn;
    delayed_data = data;
    delayed_ms = ms;
    return true;
}
void task_delete(foreground_task_ptr fn, void *data)
{
    if (delayed_task == fn && delayed_data == data)
    {
        delayed_task = NULL;
        delayed_ms = 0;
    }
}
void run_bltouch_startup(void)
{
    CHECK(startup);
    foreground_task_ptr fn = startup;
    startup = NULL;
    fn(startup_data);
}
void run_bltouch_immediate(void)
{
    CHECK(immediate);
    foreground_task_ptr fn = immediate;
    immediate = NULL;
    fn(immediate_data);
}
void run_bltouch_delayed(void)
{
    CHECK(delayed_task);
    foreground_task_ptr fn = delayed_task;
    delayed_task = NULL;
    delayed_ms = 0;
    fn(delayed_data);
}
void load_bltouch(void)
{
    void bltouch_init(void);
    hal.stream.write = write_text;
    hal.driver_reset = reset;
    hal.delay_ms = delay_ms;
    hal.probe.select = select_probe;
    hal.driver_cap.probe2 = native_probe;
    grbl.on_probe_start = probe_start;
    grbl.on_probe_completed = probe_completed;
    grbl.on_report_options = options;
    bltouch_init();
    CHECK(startup);
    run_bltouch_startup();
}
void command_bltouch(user_mcode_t command)
{
    parser_block_t block = {0};
    block.user_mcode = command;
    CHECK(grbl.user_mcode.check(command) == UserMCode_NoValueWords);
    CHECK(grbl.user_mcode.validate(&block) == Status_OK);
    grbl.user_mcode.execute(STATE_IDLE, &block);
}
status_code_t system_bltouch(const char *command)
{
    CHECK(commands);
    for (unsigned i = 0; i < commands->n_commands; i++)
        if (strcmp(commands->commands[i].command, command) == 0)
            return commands->commands[i].execute(STATE_IDLE, NULL);
    CHECK(false);
    return Status_Unhandled;
}
