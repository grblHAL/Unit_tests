#include "tmc_host.h"
system_t sys;
grbl_t grbl;
settings_t settings;
parser_state_t gc_state;
setting_details_t *tmc_settings;
const tmchal_t *tmc_drivers[3];
unsigned tmc_reads, tmc_writes, tmc_delays, tmc_warnings, tmc_previous_settings,
    tmc_previous_limits, tmc_previous_reports, tmc_previous_realtime, tmc_limit_irqs;
uint32_t tmc_registers[3][128];
uint8_t tmc_addresses[3];
bool tmc_bus_ok = true, tmc_storage_ok = true, tmc_setup_ok = true, tmc_custom_address;
char tmc_output[4096];
static uint8_t ifcnt[3];
static bool setup(settings_t *value)
{
    CHECK(value == &settings);
    return tmc_setup_ok;
}
static void previous_settings(settings_t *value, settings_changed_flags_t flags)
{
    (void)flags;
    CHECK(value == &settings);
    tmc_previous_settings++;
}
static void previous_limits(bool on, axes_signals_t homing)
{
    (void)on;
    (void)homing;
    tmc_previous_limits++;
}
static void limit_irq(limit_signals_t value)
{
    CHECK(value.min.mask == AXES_BITMASK);
    tmc_limit_irqs++;
}
static void previous_report(bool newopt)
{
    (void)newopt;
    tmc_previous_reports++;
}
static void previous_realtime(stream_write_ptr write, report_tracking_flags_t flags)
{
    (void)flags;
    write("|Previous:1");
    tmc_previous_realtime++;
}
static void output(const char *text)
{
    CHECK(strlen(tmc_output) + strlen(text) < sizeof(tmc_output));
    strcat(tmc_output, text);
}
static void delay(uint32_t ms, delay_callback_ptr callback)
{
    CHECK(!callback && (ms == 100 || ms == 7));
    if (ms == 100)
        tmc_delays++;
}
static void iterator(motor_iterator_callback_ptr callback)
{
    for (unsigned i = 0; i < 3; i++)
        callback((motor_map_t){.id = i, .axis = i});
}
static void preinit(motor_map_t motor, trinamic_driver_config_t *config)
{
    CHECK(motor.id < 3 && config->settings);
    if (tmc_custom_address)
        config->address = motor.id + 1;
}
static void postinit(motor_map_t motor, const tmchal_t *driver)
{
    CHECK(motor.id < 3 && driver);
    tmc_drivers[motor.id] = driver;
}
void tmc_uart_write(trinamic_motor_t driver, TMC_uart_write_datagram_t *packet)
{
    CHECK(driver.id < 3 && packet->msg.sync == 5 && packet->msg.slave == driver.address &&
          packet->msg.addr.write);
    uint8_t crc = packet->msg.crc;
    tmc_crc8(packet->data, 8);
    CHECK(crc == packet->msg.crc);
    tmc_addresses[driver.id] = driver.address;
    uint8_t reg = (packet->msg.addr.value & 127);
    CHECK(reg < 128);
    uint32_t value = ((uint32_t)packet->data[3] << 24) | ((uint32_t)packet->data[4] << 16) |
                     ((uint32_t)packet->data[5] << 8) | packet->data[6];
    tmc_registers[driver.id][reg] = value;
    ifcnt[driver.id]++;
    tmc_writes++;
}
TMC_uart_write_datagram_t *tmc_uart_read(trinamic_motor_t driver, TMC_uart_read_datagram_t *packet)
{
    static TMC_uart_write_datagram_t response;
    CHECK(driver.id < 3 && packet->msg.sync == 5 && packet->msg.slave == driver.address &&
          !packet->msg.addr.write);
    uint8_t crc = packet->msg.crc;
    tmc_crc8(packet->data, 4);
    CHECK(crc == packet->msg.crc);
    tmc_reads++;
    memset(&response, 0, sizeof(response));
    response.msg.sync = 5;
    response.msg.slave = tmc_bus_ok ? 255 : 0;
    response.msg.addr = packet->msg.addr;
    uint32_t value = (packet->msg.addr.value & 127) == TMC2209Reg_IFCNT
                         ? ifcnt[driver.id]
                         : tmc_registers[driver.id][(packet->msg.addr.value & 127)];
    response.data[3] = value >> 24;
    response.data[4] = value >> 16;
    response.data[5] = value >> 8;
    response.data[6] = value;
    tmc_crc8(response.data, 8);
    return &response;
}
nvs_address_t nvs_alloc(size_t size)
{
    CHECK(size && size < 1024);
    return tmc_storage_ok ? 2048 : 0;
}
bool settings_register(setting_details_t *details)
{
    CHECK(!tmc_settings);
    tmc_settings = details;
    return true;
}
void report_warning(void *text) { CHECK(text); }
bool task_add_immediate(foreground_task_ptr fn, void *data)
{
    CHECK(fn == report_warning && data);
    tmc_warnings++;
    return true;
}
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    return task_add_immediate(fn, data);
}
void report_plugin(const char *name, const char *version)
{
    CHECK(!strcmp(name, "Trinamic") && version && *version);
}
static user_mcode_type_t old_check(user_mcode_t code)
{
    (void)code;
    return UserMCode_Unsupported;
}

/* Host parser boundary follows CORE's consumed-word contract; full parser tests are separate. */
axes_signals_t gc_claim_axis_words(parser_block_t *block, axes_signals_t validate)
{
    CHECK(N_AXIS == 3);
    const parameter_words_t words[3] = {{.x = On}, {.y = On}, {.z = On}};
    axes_signals_t axes = {0};
    for (unsigned i = 0; i < 3; i++)
        if ((block->words.mask & words[i].mask) &&
            (!validate.mask || ((validate.mask & (1U << i)) && !isnan(block->values.xyz[i]))))
        {
            axes.mask |= 1U << i;
            block->words.mask &= ~words[i].mask;
        }
    return axes;
}

void tmc_prepare(void)
{
    prepare_eeprom();
    CHECK(i2c_eeprom_init());
    hal.delay_ms = delay;
    hal.driver_setup = setup;
    hal.stepper.motor_iterator = iterator;
    hal.limits.enable = previous_limits;
    hal.limits.interrupt_callback = limit_irq;
    hal.stream.write = output;
    grbl.on_settings_changed = previous_settings;
    grbl.on_report_options = previous_report;
    grbl.on_realtime_report = previous_realtime;
    grbl.user_mcode.check = old_check;
    for (unsigned i = 0; i < N_AXIS; i++)
        settings.axis[i].steps_per_mm = 80;
    trinamic_driver_if_t hooks = {.on_driver_preinit = preinit, .on_driver_postinit = postinit};
    trinamic_if_init(&hooks);
}
void tmc_load(void)
{
    CHECK(trinamic_init() && tmc_settings);
    tmc_settings->load();
}
void tmc_start(void)
{
    tmc_load();
    CHECK(hal.driver_setup(&settings));
}
void tmc_axis_command(user_mcode_t code, unsigned axis, float value)
{
    CHECK(axis < N_AXIS);
    parser_block_t block = {.user_mcode = code};
    if (axis == X_AXIS)
        block.words.x = On;
    else if (axis == Y_AXIS)
        block.words.y = On;
    else
        block.words.z = On;
    block.values.xyz[axis] = value;
    CHECK(grbl.user_mcode.check(code) != UserMCode_Unsupported);
    uint64_t before = block.words.mask;
    CHECK(grbl.user_mcode.validate(&block) == Status_OK);
    block.words.mask = before ^ block.words.mask;
    grbl.user_mcode.execute(STATE_IDLE, &block);
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
bool task_add_delayed(foreground_task_ptr fn, void *data, uint32_t delay_ms)
{
    (void)fn;
    (void)data;
    (void)delay_ms;
    CHECK(false);
    return false;
}
setting_id_t settings_get_axis_base(setting_id_t id, uint_fast8_t *idx)
{
    const setting_id_t bases[] = {Setting_AxisStepperCurrent, Setting_AxisMicroSteps,
                                  Setting_AxisExtended0, Setting_AxisExtended1,
                                  Setting_AxisExtended2};
    for (unsigned i = 0; i < sizeof(bases) / sizeof(*bases); i++)
        if (id >= bases[i] && id < bases[i] + N_AXIS)
        {
            *idx = id - bases[i];
            return bases[i];
        }
    CHECK(false);
    return Setting_SettingsMax;
}

status_code_t tmc_set(setting_id_t base, unsigned axis, uint_fast16_t value)
{
    CHECK(axis < N_AXIS && tmc_settings);
    for (unsigned i = 0; i < tmc_settings->n_settings; i++)
    {
        const setting_detail_t *d = &tmc_settings->settings[i];
        if (d->id == base)
            return ((setting_set_int_ptr)d->value)(base + axis, value);
    }
    CHECK(false);
    return Status_Unhandled;
}
