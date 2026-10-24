#include "ppi_host.h"
system_t sys;
grbl_hal_t hal;
grbl_t grbl;
settings_t settings;
parser_state_t gc_state;
spindle_ptrs_t *ppi_motor;
bool ppi_core_handles;
unsigned ppi_pulses, ppi_steps, ppi_wakes, ppi_updates, ppi_selected, ppi_parser_inits,
    ppi_completions, ppi_previous_reports, ppi_fallback_checks, ppi_fallback_validates,
    ppi_fallback_executes;
uint_fast16_t ppi_width, ppi_core_rate, ppi_core_width;
unsigned ppi_locations[64];
static spindle_ptrs_t descriptor;
static spindle_pwm_t pwm_data;
static void pulse(spindle_ptrs_t *motor, uint_fast16_t width)
{
    CHECK(motor == ppi_motor && ppi_pulses < 64);
    ppi_width = width;
    ppi_locations[ppi_pulses++] = ppi_steps + 1;
}
static void update_pwm(spindle_ptrs_t *motor, uint_fast16_t level)
{
    CHECK(motor == ppi_motor);
    (void)level;
    ppi_updates++;
}
static void update_rpm(spindle_ptrs_t *motor, float rpm)
{
    CHECK(motor == ppi_motor && rpm >= 0);
    ppi_updates++;
}
static void set_state(spindle_ptrs_t *motor, spindle_state_t state, float rpm)
{
    CHECK(motor);
    (void)state;
    (void)rpm;
}
static spindle_state_t get_state(spindle_ptrs_t *motor)
{
    CHECK(motor);
    return (spindle_state_t){0};
}
static void wake(void) { ppi_wakes++; }
static void step(stepper_t *data)
{
    CHECK(data);
    ppi_steps++;
}
static void selected(spindle_ptrs_t *motor)
{
    CHECK(motor);
    ppi_selected++;
}
static void parser_init(parser_state_t *parser)
{
    CHECK(parser == &gc_state);
    ppi_parser_inits++;
}
static void completed(program_flow_t flow, bool check)
{
    CHECK(flow == ProgramFlow_CompletedM30);
    (void)check;
    ppi_completions++;
}
static void report_options(bool newopt)
{
    (void)newopt;
    ppi_previous_reports++;
}
static user_mcode_type_t fallback_check(user_mcode_t code)
{
    CHECK(code == RGB_WriteLEDs);
    ppi_fallback_checks++;
    return UserMCode_Normal;
}
static status_code_t fallback_validate(parser_block_t *block)
{
    CHECK(block->user_mcode == RGB_WriteLEDs);
    ppi_fallback_validates++;
    return Status_GcodeValueOutOfRange;
}
static void fallback_execute(sys_state_t state, parser_block_t *block)
{
    CHECK(state == STATE_IDLE && block->user_mcode == RGB_WriteLEDs);
    ppi_fallback_executes++;
}
bool gc_laser_ppi_enable(uint_fast16_t rate, uint_fast16_t width)
{
    ppi_core_rate = rate;
    ppi_core_width = width;
    return ppi_core_handles;
}
bool settings_add_spindle_type(const char *name)
{
    CHECK(name && *name);
    return true;
}
void report_plugin(const char *name, const char *version)
{
    CHECK(!strcmp(name, "Laser PPI") && version && *version);
}
void gc_spindle_off(void) { CHECK(false); }
void report_add_realtime(report_tracking_t report)
{
    (void)report;
    CHECK(false);
}
const setting_detail_t *setting_get_details(setting_id_t id, setting_details_t **details)
{
    (void)id;
    (void)details;
    CHECK(false);
    return NULL;
}
uint32_t setting_get_int_value(const setting_detail_t *setting, uint_fast16_t offset)
{
    (void)setting;
    (void)offset;
    CHECK(false);
    return 0;
}
sys_state_t state_get(void)
{
    CHECK(false);
    return STATE_IDLE;
}
void task_delete(foreground_task_ptr fn, void *data)
{
    (void)fn;
    (void)data;
    CHECK(false);
}
bool task_add_immediate(foreground_task_ptr fn, void *data)
{
    (void)fn;
    (void)data;
    CHECK(false);
    return false;
}
bool task_add_delayed(foreground_task_ptr fn, void *data, uint32_t delay_ms)
{
    (void)fn;
    (void)data;
    (void)delay_ms;
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
void st_rpm_changed(float rpm)
{
    (void)rpm;
    CHECK(false);
}
bool protocol_buffer_synchronize(void)
{
    CHECK(false);
    return false;
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
void ppi_prepare(bool pwm, bool capability)
{
    settings.mode = Mode_Laser;
    settings.pwm_spindle.rpm_max = 1000;
    hal.stepper.wake_up = wake;
    hal.stepper.pulse_start = step;
    grbl.on_spindle_selected = selected;
    grbl.on_parser_init = parser_init;
    grbl.on_program_completed = completed;
    grbl.on_report_options = report_options;
    grbl.user_mcode = (user_mcode_ptrs_t){
        .check = fallback_check, .validate = fallback_validate, .execute = fallback_execute};
    pwm_data.settings = &settings.pwm_spindle;
    descriptor = (spindle_ptrs_t){.type = SpindleType_PWM,
                                  .cap = {.laser = On, .variable = On},
                                  .context.pwm = &pwm_data,
                                  .set_state = set_state,
                                  .get_state = get_state,
                                  .pulse_on = capability ? pulse : NULL,
                                  .update_pwm = pwm ? update_pwm : NULL,
                                  .update_rpm = pwm ? NULL : update_rpm};
    ppi_init();
    CHECK(spindle_register(&descriptor, "Host laser") == 0 && spindle_select(0));
    ppi_motor = spindle_get(0);
    CHECK(ppi_motor && ppi_selected == 1);
}
void ppi_command(user_mcode_t code, float value, sys_state_t state)
{
    parser_block_t block = {.user_mcode = code, .values.p = value, .words.p = On};
    CHECK(grbl.user_mcode.check(code) == UserMCode_Normal);
    parameter_words_t supplied = block.words;
    CHECK(grbl.user_mcode.validate(&block) == Status_OK && !block.words.p);
    block.words.mask = supplied.mask ^ block.words.mask;
    grbl.user_mcode.execute(state, &block);
}
void ppi_move(unsigned steps, float steps_per_mm)
{
    st_block_t block = {.steps_per_mm = steps_per_mm};
    stepper_t stepper = {.new_block = true, .step_out.bits = 1, .exec_block = &block};
    for (unsigned i = 0; i < steps; i++)
    {
        hal.stepper.pulse_start(&stepper);
        stepper.new_block = false;
    }
}
void system_raise_alarm(alarm_code_t alarm)
{
    (void)alarm;
    CHECK(false);
}
