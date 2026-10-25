#include "job_host.h"
grbl_t grbl;
system_t sys;
settings_t settings;
setting_details_t *job_settings;
bool job_storage = true;
unsigned job_warnings, job_resets;
char job_output[4096];
job_motion_t job_motions[64];
unsigned job_motion_count, job_cancels, job_completions, job_feedback;
bool job_spindle_on;
uint_fast16_t job_planner_free = 16;
static ioport_interrupt_callback_ptr needle_irq;
static uint8_t needle_port;
static uint32_t job_ticks = 1000;
static spindle_ptrs_t needle_spindle;
int32_t job_serial_read(void) { return SERIAL_NO_DATA; }
static void cancel_read(void) { job_cancels++; }
static uint32_t elapsed_ticks(void) { return job_ticks; }
static void set_spindle(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    CHECK(spindle == &needle_spindle && rpm == (state.on ? 1.0f : 0.0f));
    job_spindle_on = state.on;
}
static void program_completed(program_flow_t flow, bool check)
{
    CHECK(flow == ProgramFlow_CompletedM30 && !check);
    job_completions++;
}
static message_code_t feedback(message_code_t message)
{
    CHECK(message == Message_ProgramEnd);
    job_feedback++;
    return message;
}
void job_sync(bool enabled)
{
    CHECK(job_settings);
    for (unsigned i = 0; i < job_settings->n_settings; i++)
        if (job_settings->settings[i].id == Setting_UserDefined_3)
        {
            CHECK(job_settings->settings[i].datatype == Format_Bool);
            *(bool *)job_settings->settings[i].value = enabled;
            return;
        }
    CHECK(false);
}
void job_needle(void)
{
    CHECK(needle_irq);
    job_ticks += 100;
    needle_irq(needle_port, false);
}
static void write_text(const char *text)
{
    CHECK(text && strlen(job_output) + strlen(text) < sizeof(job_output));
    strcat(job_output, text);
}
static void previous_options(bool newopt) { (void)newopt; }
static void previous_reset(void) { job_resets++; }
static void previous_state(sys_state_t state) { (void)state; }
static void previous_realtime(sys_state_t state) { (void)state; }
static xbar_t trigger_pin;
static xbar_t *pin_info(io_port_direction_t dir, uint8_t port)
{
    return dir == Port_Input && port == 0 ? &trigger_pin : NULL;
}
static void pin_description(io_port_direction_t dir, uint8_t port, const char *text)
{
    CHECK(dir == Port_Input && port == 0);
    trigger_pin.description = text;
}
static int32_t pin_wait(uint8_t port, wait_mode_t mode, float timeout)
{
    CHECK(port == 0 && mode == WaitMode_Immediate && timeout == 0);
    return 0;
}
static bool pin_irq(uint8_t physical, uint8_t user, pin_irq_mode_t mode,
                    ioport_interrupt_callback_ptr handler)
{
    CHECK(physical == 0 && user < N_AUX_DIN_MAX);
    CHECK((mode == IRQ_Mode_None && handler == NULL) ||
          (mode == IRQ_Mode_Falling && handler != NULL));
    needle_irq = handler;
    needle_port = user;
    return true;
}
void job_prepare(void)
{
    prepare_eeprom();
    CHECK(i2c_eeprom_init());
    hal.stream = (io_stream_t){.type = StreamType_Serial,
                               .write = write_text,
                               .read = job_serial_read,
                               .cancel_read_buffer = cancel_read};
    hal.get_elapsed_ticks = elapsed_ticks;
    needle_spindle.set_state = set_spindle;
    grbl.on_program_completed = program_completed;
    grbl.report.feedback_message = feedback;
    hal.driver_reset = previous_reset;
    grbl.on_report_options = previous_options;
    grbl.on_state_change = previous_state;
    grbl.on_execute_realtime = previous_realtime;
    static io_ports_data_t ports;
    static io_digital_t digital;
    trigger_pin = (xbar_t){.id = 0, .function = Input_Aux0, .cap.input = On};
    trigger_pin.cap.irq_mode = IRQ_Mode_RisingFalling;
    ports.in.n_ports = 1;
    digital = (io_digital_t){.ports = &ports,
                             .get_pin_info = pin_info,
                             .set_pin_description = pin_description,
                             .wait_on_input = pin_wait,
                             .register_interrupt_handler = pin_irq};
    CHECK(ioports_add_digital(&digital));
    embroidery_init();
    if (job_settings)
    {
        job_settings->restore();
        job_settings->load();
    }
}
vfs_file_t *job_dst(const uint8_t *stitches, size_t length)
{
    static const embedded_file_t *files[2];
    CHECK(length && length < 1024);
    embedded_file_t *file = calloc(1, sizeof(*file) + 512 + length);
    CHECK(file);
    file->name = "job.dst";
    file->size = 512 + length;
    file->st_mode.read_only = On;
    uint8_t *data = (uint8_t *)file->data;
    memset(data, ' ', 512);
    const char header[] = "LA:Pocket\rST:4\rCO:2\r+X:121\r-X:20\r+Y:80\r-Y:11\r";
    memcpy(data, header, sizeof(header) - 1);
    data[sizeof(header) - 1] = ASCII_EOF;
    memcpy(data + 512, stitches, length);
    files[0] = file;
    CHECK(fs_embedded_mount(files));
    vfs_file_t *opened = vfs_open("/embedded/job.dst", "r");
    CHECK(opened);
    return opened;
}
vfs_file_t *job_pes(const uint8_t *stitches, size_t length)
{
    static const embedded_file_t *files[2];
    CHECK(length && length < 1024);
    embedded_file_t *file = calloc(1, sizeof(*file) + 580 + length);
    CHECK(file);
    file->name = "job.pes";
    file->size = 580 + length;
    file->st_mode.read_only = On;
    uint8_t *data = (uint8_t *)file->data;
    memcpy(data, "#PES0001", 8);
    data[8] = 32;
    memcpy(data + 32, "LA:Sample", 9);
    data[32 + 48] = 1;
    data[32 + 49] = 5;
    data[32 + 50] = 2;
    data[32 + 512 + 8] = 120;
    data[32 + 512 + 10] = 80;
    memcpy(data + 580, stitches, length);
    files[0] = file;
    CHECK(fs_embedded_mount(files));
    vfs_file_t *opened = vfs_open("/embedded/job.pes", "r");
    CHECK(opened);
    return opened;
}
nvs_address_t nvs_alloc(size_t size)
{
    CHECK(size && size < 256);
    return job_storage ? 2048 : 0;
}
bool settings_register(setting_details_t *details)
{
    CHECK(details);
    for (unsigned i = 0; i < details->n_settings; i++)
        if (details->settings[i].id == Setting_UserDefined_0)
        {
            CHECK(!job_settings);
            job_settings = details;
        }
    return true;
}
void report_warning(void *message)
{
    CHECK(message);
    job_warnings++;
}
void report_message(const char *text, message_type_t type)
{
    (void)type;
    write_text(text);
}
void report_plugin(const char *name, const char *version) { CHECK(name && version); }
bool task_run_on_startup(foreground_task_ptr task, void *data)
{
    CHECK(task == report_warning);
    task(data);
    return true;
}
bool task_add_immediate(foreground_task_ptr task, void *data)
{
    (void)task;
    (void)data;
    CHECK(false);
    return false;
}
status_code_t mc_line(float *target, plan_line_data_t *data)
{
    CHECK(target && data && job_motion_count < 64);
    job_motion_t *motion = &job_motions[job_motion_count++];
    memcpy(motion->target.values, target, sizeof(motion->target.values));
    motion->feed = data->feed_rate;
    motion->rapid = data->condition.rapid_motion;
    return Status_Handled;
}
void plan_data_init(plan_line_data_t *data)
{
    CHECK(data);
    memset(data, 0, sizeof(*data));
    data->spindle.hal = &needle_spindle;
}
uint_fast16_t plan_get_block_buffer_available(void) { return job_planner_free; }
void protocol_buffer_synchronize(void) { CHECK(false); }
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
void system_convert_array_steps_to_mpos(float *position, int32_t *steps)
{
    CHECK(position && steps);
    for (unsigned i = 0; i < N_AXIS; i++)
    {
        CHECK(steps[i] == 0);
        position[i] = 0;
    }
}

parser_state_t gc_state;
axes_signals_t limit_signals_merge(limit_signals_t signals)
{
    (void)signals;
    CHECK(false);
    return (axes_signals_t){0};
}
void setting_remove_elements(setting_id_t id, uint32_t mask, bool trim)
{
    (void)id;
    (void)mask;
    (void)trim;
    CHECK(false);
}
void settings_write_global(void) { CHECK(false); }
void task_execute(bool systick)
{
    (void)systick;
    CHECK(false);
}
bool protocol_enqueue_realtime_command(uint8_t c)
{
    (void)c;
    CHECK(false);
    return false;
}
sys_state_t state_get(void) { return STATE_IDLE; }
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
void gc_filestream_changed(vfs_file_t *file) { CHECK(file == hal.stream.file); }
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
