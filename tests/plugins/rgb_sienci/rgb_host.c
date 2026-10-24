#include "rgb_host.h"
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
rgb_color_t pixels[2][32];
unsigned counts[2], writes[2], chains, warnings, messages;
uint8_t brightness[2] = {255, 255};
bool bus_busy;
uint32_t now, last_delay;
unsigned pending;
sys_state_t machine_state = STATE_IDLE;
static struct
{
    foreground_task_ptr fn;
    void *data;
    uint32_t due;
} tasks[128];
static void out0(uint16_t device, rgb_color_t color)
{
    CHECK(device < hal.rgb0.num_devices && device < 32);
    pixels[0][device] = color;
    counts[0]++;
}
static void out1(uint16_t device, rgb_color_t color)
{
    CHECK(device < hal.rgb1.num_devices && device < 32);
    pixels[1][device] = color;
    counts[1]++;
}
static void write0(void) { writes[0]++; }
static void write1(void) { writes[1]++; }
static uint8_t intensity0(uint8_t value)
{
    uint8_t old = brightness[0];
    brightness[0] = value;
    return old;
}
static uint8_t intensity1(uint8_t value)
{
    uint8_t old = brightness[1];
    brightness[1] = value;
    return old;
}
bool modbus_isbusy(void) { return bus_busy; }
sys_state_t state_get(void) { return machine_state; }
bool task_add_delayed(foreground_task_ptr fn, void *data, uint32_t delay)
{
    CHECK(fn && pending < 128);
    tasks[pending].fn = fn;
    tasks[pending].data = data;
    tasks[pending++].due = now + delay;
    last_delay = delay;
    return true;
}
bool task_add_immediate(foreground_task_ptr fn, void *data)
{
    return task_add_delayed(fn, data, 0);
}
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    return task_add_delayed(fn, data, 0);
}
void rgb_run_next(void)
{
    CHECK(pending);
    unsigned next = 0;
    for (unsigned i = 1; i < pending; i++)
        if (tasks[i].due < tasks[next].due)
            next = i;
    foreground_task_ptr fn = tasks[next].fn;
    void *data = tasks[next].data;
    now = tasks[next].due;
    tasks[next] = tasks[--pending];
    fn(data);
}
void report_warning(void *text)
{
    CHECK(text);
    warnings++;
}
void report_message(const char *text, message_type_t type)
{
    CHECK(text && type == Message_Info);
    messages++;
}
void report_plugin(const char *name, const char *version)
{
    CHECK(strcmp(name, "SIENCI Indicator Light") == 0);
#if STATUS_LIGHT_ENABLE == 2
    CHECK(strcmp(version, "2.0") == 0);
#else
    CHECK(strcmp(version, "3.0") == 0);
#endif
    chains++;
}
static void previous_options(bool newopt)
{
    (void)newopt;
    chains++;
}
static void previous_state(sys_state_t state)
{
    (void)state;
    chains++;
}
static void previous_complete(program_flow_t flow, bool check)
{
    (void)flow;
    (void)check;
    chains++;
}
static void previous_tool(tool_data_t *tool)
{
    CHECK(tool);
    chains++;
}
static user_mcode_type_t previous_check(user_mcode_t code)
{
    CHECK(code != RGB_Inspection_Light);
    chains++;
    return UserMCode_Normal;
}
static status_code_t previous_validate(parser_block_t *block)
{
    CHECK(block->user_mcode != RGB_Inspection_Light);
    chains++;
    return Status_SettingDisabled;
}
static void previous_execute(sys_state_t state, parser_block_t *block)
{
    (void)state;
    CHECK(block->user_mcode != RGB_Inspection_Light);
    chains++;
}
void rgb_prepare(void)
{
    hal.rgb0 = (rgb_ptr_t){.out = out0,
                           .write = write0,
                           .set_intensity = intensity0,
                           .cap = {.R = 255, .G = 255, .B = 255},
                           .num_devices = 16};
    hal.rgb1 = (rgb_ptr_t){.out = out1,
                           .write = write1,
                           .set_intensity = intensity1,
                           .cap = {.R = 255, .G = 255, .B = 255},
                           .num_devices = 4};
    grbl.on_report_options = previous_options;
    grbl.on_state_change = previous_state;
    grbl.on_program_completed = previous_complete;
    grbl.on_tool_selected = previous_tool;
    grbl.on_tool_changed = previous_tool;
    grbl.user_mcode = (user_mcode_ptrs_t){
        .check = previous_check, .validate = previous_validate, .execute = previous_execute};
}
void rgb_start(void)
{
    rgb_prepare();
    status_light_init();
    CHECK(pending == 1);
    rgb_run_next();
    CHECK(warnings == 0);
}
void rgb_state(sys_state_t state)
{
    machine_state = state;
    grbl.on_state_change(state);
}
void rgb_expect(unsigned strip, unsigned r, unsigned g, unsigned b)
{
    unsigned n = strip ? hal.rgb1.num_devices : hal.rgb0.num_devices;
    CHECK(n);
    for (unsigned i = 0; i < n; i++)
        CHECK(pixels[strip][i].R == r && pixels[strip][i].G == g && pixels[strip][i].B == b);
}
status_code_t rgb_command(float zone, float mode, float intensity, bool execute)
{
    parser_block_t block = {0};
    block.user_mcode = RGB_Inspection_Light;
    block.words.p = block.words.q = block.words.s = 1;
    block.values.p = zone;
    block.values.q = mode;
    block.values.s = intensity;
    CHECK(grbl.user_mcode.check(block.user_mcode) == UserMCode_Normal);
    status_code_t status = grbl.user_mcode.validate(&block);
    if (status == Status_OK)
    {
        CHECK(!block.words.p && !block.words.q && !block.words.s && block.user_mcode_sync);
        if (execute)
            grbl.user_mcode.execute(machine_state, &block);
    }
    return status;
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
