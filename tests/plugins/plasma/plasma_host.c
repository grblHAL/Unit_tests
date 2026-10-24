#include "plasma_host.h"
system_t sys;
grbl_t grbl;
settings_t settings;
parser_state_t gc_state;
setting_details_t *plasma_details;
unsigned plasma_warnings, plasma_prior_comments, plasma_prior_reports, plasma_steps;
char plasma_output[8192];
bool plasma_storage_ok = true;
static sys_commands_t *commands;
static xbar_t pins[3];
static uint64_t micros;
static uint64_t get_micros(void) { return micros; }
static void step(axes_signals_t value, axes_signals_t dir)
{
    CHECK((value.mask & ~Z_AXIS_BIT) == 0);
    (void)dir;
    plasma_steps++;
}
static void previous_settings(settings_t *value, settings_changed_flags_t changed)
{
    (void)changed;
    CHECK(value == &settings);
}
static void previous_report(bool newopt)
{
    (void)newopt;
    plasma_prior_reports++;
}
static status_code_t previous_comment(char *text)
{
    CHECK(text);
    plasma_prior_comments++;
    return Status_Unhandled;
}
static void output(const char *text)
{
    CHECK(strlen(plasma_output) + strlen(text) < sizeof(plasma_output));
    strcat(plasma_output, text);
}
static xbar_t *pin_info(io_port_direction_t direction, uint8_t port)
{
    return direction == Port_Input && port < 3 ? &pins[port] : NULL;
}
static void pin_description(io_port_direction_t direction, uint8_t port, const char *description)
{
    CHECK(direction == Port_Input && port < 3);
    pins[port].description = description;
}
static int32_t read_input(uint8_t port, wait_mode_t mode, float timeout)
{
    (void)mode;
    (void)timeout;
    CHECK(port < 3);
    return 1;
}
static float pin_value(xbar_t *pin)
{
    CHECK(pin && pin->id < 3);
    return 1;
}
nvs_address_t nvs_alloc(size_t size)
{
    static nvs_address_t next = 2048;
    CHECK(size && size < 1024);
    if (!plasma_storage_ok)
        return 0;
    nvs_address_t address = next;
    next += (size + NVS_CRC_BYTES + 3) & ~3U;
    CHECK(next < 8192);
    return address;
}
bool settings_register(setting_details_t *details)
{
    CHECK(details);
    for (unsigned i = 0; i < details->n_settings; i++)
        if (details->settings[i].id == Setting_THC_Mode)
        {
            CHECK(!plasma_details);
            plasma_details = details;
        }
    return true;
}
void system_register_commands(sys_commands_t *value)
{
    CHECK(value->n_commands == 1 && !strcmp(value->commands[0].command, "EM"));
    commands = value;
}
status_code_t plasma_list(void)
{
    CHECK(commands);
    return commands->commands[0].execute(STATE_IDLE, NULL);
}
status_code_t plasma_comment(char *text)
{
    CHECK(grbl.on_gcode_comment);
    return grbl.on_gcode_comment(text);
}
void report_warning(void *data) { CHECK(data); }
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    CHECK(fn == report_warning && data);
    plasma_warnings++;
    return true;
}
void report_plugin(const char *name, const char *version)
{
    CHECK(name && version);
    output(name);
}
void report_message(const char *text, message_type_t type)
{
    (void)type;
    output(text);
    output("\n");
}
void plasma_prepare(unsigned inputs, bool output_step)
{
    CHECK(inputs <= 3);
    prepare_eeprom();
    CHECK(i2c_eeprom_init());
    hal.get_micros = get_micros;
    hal.stepper.output_step = output_step ? step : NULL;
    hal.stream.write = output;
    grbl.on_settings_changed = previous_settings;
    grbl.on_report_options = previous_report;
    grbl.on_gcode_comment = previous_comment;
    settings.steppers.pulse_microseconds = 4;
    for (unsigned i = 0; i < N_AXIS; i++)
        settings.axis[i] =
            (axis_settings_t){.steps_per_mm = 80, .acceleration = 360000, .max_rate = 1000};
    if (inputs)
    {
        for (unsigned i = 0; i < inputs; i++)
            pins[i] = (xbar_t){
                .id = i, .function = Input_Aux0 + i, .cap.input = On, .get_value = pin_value};
        static io_ports_data_t ports;
        ports.in.n_ports = inputs;
        static io_digital_t digital;
        digital = (io_digital_t){.ports = &ports,
                                 .get_pin_info = pin_info,
                                 .set_pin_description = pin_description,
                                 .wait_on_input = read_input};
        CHECK(ioports_add_digital(&digital));
    }
}
void plasma_load(void)
{
    plasma_init();
    CHECK(plasma_details);
    plasma_details->load();
}
material_t plasma_material(int id)
{
    material_t result = {.id = id, .thc_status = true};
    for (unsigned i = 0; i < 12; i++)
        result.params[i] = NAN;
    result.pierce_height = 3;
    result.pierce_delay = 0.5f;
    result.cut_height = 1;
    result.feed_rate = 900;
    strcpy(result.name, "Steel");
    return result;
}
void plasma_mount(const embedded_file_t **files)
{
    CHECK(fs_embedded_mount(files));
    vfs_drives_t *dh = vfs_drives_open();
    CHECK(dh);
    const vfs_t *backend = NULL;
    vfs_drive_t *drive;
    while ((drive = vfs_drives_read(dh, true)))
        if (!strcmp(drive->name, "embedded"))
            backend = drive->fs;
    vfs_drives_close(dh);
    CHECK(backend && vfs_mount(NULL, "/", backend, (vfs_st_mode_t){.read_only = On}));
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
void setting_remove_elements(setting_id_t id, uint32_t mask, bool trim)
{
    CHECK(id == Setting_THC_Mode && mask == 0b1101 && trim);
}
bool task_add_systick(foreground_task_ptr fn, void *data)
{
    (void)fn;
    (void)data;
    CHECK(false);
    return false;
}
void task_delete(foreground_task_ptr fn, void *data)
{
    (void)fn;
    (void)data;
    CHECK(false);
}
void plan_feed_override(override_t feed, override_t rapid)
{
    (void)feed;
    (void)rapid;
    CHECK(false);
}
sys_state_t state_get(void)
{
    CHECK(false);
    return STATE_IDLE;
}
void plan_sync_position(void) { CHECK(false); }
void system_convert_array_steps_to_mpos(float *position, int32_t *steps)
{
    (void)position;
    (void)steps;
    CHECK(false);
}
bool task_add_delayed(foreground_task_ptr fn, void *data, uint32_t delay)
{
    (void)fn;
    (void)data;
    (void)delay;
    CHECK(false);
    return false;
}
void plan_data_init(plan_line_data_t *data)
{
    (void)data;
    CHECK(false);
}
float gc_get_offset(uint_fast8_t axis, bool realtime)
{
    (void)axis;
    (void)realtime;
    CHECK(false);
    return 0;
}
status_code_t mc_line(float *target, plan_line_data_t *data)
{
    (void)target;
    (void)data;
    CHECK(false);
    return Status_Unhandled;
}
bool protocol_buffer_synchronize(void)
{
    CHECK(false);
    return false;
}
uint8_t ngc_float_decimals(void) { return 3; }
void settings_write_global(void) { CHECK(false); }
setting_id_t settings_get_axis_base(setting_id_t id, uint_fast8_t *idx)
{
    (void)id;
    (void)idx;
    CHECK(false);
    return Setting_SettingsMax;
}
bool stream_await_tx_clear(const io_stream_t *stream)
{
    CHECK(stream == &hal.stream);
    return true;
}
