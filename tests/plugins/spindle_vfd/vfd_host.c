#include "vfd_host.h"
system_t sys;
grbl_t grbl;
settings_t settings;
setting_details_t *vfd_settings;
spindle_ptrs_t *vfd_motor;
unsigned vfd_requests, vfd_flushes, vfd_silences, vfd_alarms, vfd_previous_settings,
    vfd_previous_reports, vfd_previous_selected;
uint32_t vfd_ticks;
bool vfd_bus_up = true, vfd_storage_ok = true;
unsigned vfd_reject, vfd_exception;
uint16_t vfd_feedback = 10000;
uint16_t vfd_max_rpm = 24000;
uint16_t vfd_rpm_50hz = 3000, vfd_max_amps = 100, vfd_amps = 25;
uint16_t vfd_poles = 2, vfd_min_frequency = 100;
#if TEST_NOWFOREVER
uint16_t vfd_max_frequency = 40000;
#else
uint16_t vfd_max_frequency = 4000;
#endif
unsigned vfd_resets;
modbus_message_t vfd_messages[64];
bool vfd_blocking[64];
static foreground_task_ptr tasks[8];
static void *task_data[8];
static unsigned task_count;
static bool bus_up(void) { return vfd_bus_up; }
static void flush(void) { vfd_flushes++; }
static void silence(const modbus_silence_timeout_t *timeout)
{
#if TEST_HUANYANG1
    CHECK(timeout && timeout->b2400 == 16 && timeout->b4800 == 8);
    CHECK(timeout->b9600 == 6 && timeout->b19200 == 6 && timeout->b38400 == 6 && timeout->b115200 == 6);
#else
    CHECK(timeout == NULL);
#endif
    vfd_silences++;
}
static uint32_t ticks(void) { return vfd_ticks; }
static bool send_message(modbus_message_t *message, const modbus_callbacks_t *callbacks, bool block)
{
    CHECK(vfd_requests < 64);
#if TEST_HUANYANG1
    CHECK(message->tx_length == (message->adu[1] == ModBus_WriteCoil ? 7 :
                                message->adu[1] == ModBus_ReadHoldingRegisters ? 6 : 8));
#elif TEST_NOWFOREVER
    CHECK(message->tx_length == (message->adu[1] == ModBus_WriteRegisters ? 11 : 8));
#else
    CHECK(message->tx_length == 8);
#endif
    CHECK(callbacks && callbacks->retries == VFD_RETRIES &&
          callbacks->retry_delay == VFD_RETRY_DELAY);
    vfd_messages[vfd_requests] = *message;
    vfd_blocking[vfd_requests++] = block;
    if (vfd_reject && vfd_requests == vfd_reject)
        return false;
    if (vfd_exception && vfd_requests == vfd_exception)
        callbacks->on_rx_exception(ModBus_IllegalDataAddress, message->context);
    else
    {
        modbus_message_t reply = *message;
#if TEST_HUANYANG1
        if (message->adu[1] == ModBus_ReadCoils || message->adu[1] == ModBus_ReadInputRegisters)
        {
            CHECK(message->rx_length == 8 && message->adu[2] == 3);
            uint16_t value = 0;
            if (message->adu[1] == ModBus_ReadCoils)
            {
                switch (message->adu[3])
                {
                    case 0x90: value = vfd_rpm_50hz; break;
                    case 0x0b: value = vfd_min_frequency; break;
                    case 0x05: value = vfd_max_frequency; break;
                    case 0x8e: value = vfd_max_amps; break;
                    default: CHECK(false);
                }
            }
            else
            {
                CHECK(message->adu[3] == 1 || message->adu[3] == 2);
                value = message->adu[3] == 1 ? vfd_feedback : vfd_amps;
            }
            reply.adu[4] = value >> 8;
            reply.adu[5] = value & 255;
        }
#else
        if (message->adu[1] == ModBus_ReadHoldingRegisters)
        {
#if TEST_NOWFOREVER
            uint16_t reg = (message->adu[2] << 8) | message->adu[3];
            CHECK(reg == 7 || reg == 0x502);
            CHECK(message->rx_length == (reg == 7 ? 9 : 7));
            reply.adu[2] = reg == 7 ? 4 : 2;
            uint16_t value = reg == 7 ? vfd_max_frequency : vfd_feedback;
            reply.adu[3] = value >> 8;
            reply.adu[4] = value & 255;
            if (reg == 7)
            {
                reply.adu[5] = vfd_min_frequency >> 8;
                reply.adu[6] = vfd_min_frequency & 255;
            }
#elif TEST_HUANYANG2
            CHECK(message->rx_length == 8);
            uint16_t reg = (message->adu[2] << 8) | message->adu[3];
            CHECK(reg == 0xb005 || reg == 0x700c);
            uint16_t value = reg == 0xb005 ? vfd_max_rpm : vfd_feedback;
            reply.adu[4] = value >> 8;
            reply.adu[5] = value & 255;
#else
            CHECK(message->rx_length == 7);
            uint16_t value = vfd_feedback;
#if TEST_H100
            uint16_t reg = (message->adu[2] << 8) | message->adu[3];
            if (reg == 143)
                value = vfd_poles;
            else if (reg == 11)
                value = vfd_min_frequency;
            else
            {
                CHECK(reg == 5);
                value = vfd_max_frequency;
            }
#endif
            reply.adu[2] = 2;
            reply.adu[3] = value >> 8;
            reply.adu[4] = value & 255;
#endif
        }
#if TEST_H100
        else if (message->adu[1] == ModBus_ReadInputRegisters)
        {
            CHECK(message->rx_length == 9);
            reply.adu[2] = 4;
            reply.adu[3] = vfd_feedback >> 8;
            reply.adu[4] = vfd_feedback & 255;
            reply.adu[5] = reply.adu[6] = 0;
        }
#endif
#endif
        callbacks->on_rx_packet(&reply);
    }
    return true;
}
nvs_address_t nvs_alloc(size_t size)
{
    CHECK(size && size < 256);
    return vfd_storage_ok ? 2048 : 0;
}
bool settings_register(setting_details_t *details)
{
    CHECK(!vfd_settings);
    vfd_settings = details;
    return true;
}
bool settings_add_spindle_type(const char *name)
{
    CHECK(name && *name);
    return true;
}
void report_add_realtime(report_tracking_t report) { CHECK(report == Report_SpindleId); }
void report_plugin(const char *name, const char *version)
{
    CHECK(name && *name && version && *version);
}
void report_warning(void *message) { CHECK(message); }
void system_raise_alarm(alarm_code_t alarm)
{
    CHECK(alarm == Alarm_ModbusException);
    vfd_alarms++;
}
void gc_spindle_off(void)
{
    spindle_ptrs_t *motor = spindle_get(0);
    CHECK(motor);
    motor->set_state(motor, (spindle_state_t){0}, 0);
}
static void previous_settings(settings_t *value, settings_changed_flags_t changed)
{
    (void)changed;
    CHECK(value == &settings);
    vfd_previous_settings++;
}
static void previous_reports(bool newopt)
{
    (void)newopt;
    vfd_previous_reports++;
}
static void previous_selected(spindle_ptrs_t *motor)
{
    CHECK(motor);
    vfd_previous_selected++;
}
bool task_add_immediate(foreground_task_ptr fn, void *data)
{
    CHECK(task_count < 8);
    tasks[task_count] = fn;
    task_data[task_count++] = data;
    return true;
}
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    return task_add_immediate(fn, data);
}
void vfd_run_tasks(void)
{
    unsigned count = task_count;
    task_count = 0;
    for (unsigned i = 0; i < count; i++)
        tasks[i](task_data[i]);
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
static void base_reset(void) { vfd_resets++; }
void vfd_prepare(bool transport)
{
    prepare_eeprom();
    CHECK(i2c_eeprom_init());
    hal.get_elapsed_ticks = ticks;
    hal.driver_reset = base_reset;
    settings.spindle.at_speed_tolerance = 5;
    settings.pwm_spindle.rpm_min = 0;
    settings.pwm_spindle.rpm_max = 24000;
    grbl.on_settings_changed = previous_settings;
    grbl.on_report_options = previous_reports;
    grbl.on_spindle_selected = previous_selected;
    if (transport)
    {
        const modbus_api_t bus = {.interface = Modbus_InterfaceRTU,
                                  .is_up = bus_up,
                                  .flush_queue = flush,
                                  .set_silence = silence,
                                  .send = send_message};
        CHECK(modbus_register_api(&bus));
    }
    vfd_init();
}
void vfd_start(void)
{
    CHECK(vfd_settings);
    vfd_settings->load();
    CHECK(spindle_select(0));
    vfd_motor = spindle_get(0);
    CHECK(vfd_motor && vfd_motor->type == SpindleType_VFD && vfd_get_active());
}
void vfd_clear_requests(void) { vfd_requests = vfd_reject = vfd_exception = 0; }
static const setting_detail_t *detail(setting_id_t id)
{
    CHECK(vfd_settings);
    for (unsigned i = 0; i < vfd_settings->n_settings; i++)
        if (vfd_settings->settings[i].id == id)
            return &vfd_settings->settings[i];
    CHECK(false);
    return NULL;
}
void vfd_word(setting_id_t id, uint16_t value)
{
    const setting_detail_t *d = detail(id);
    CHECK(d->datatype == Format_Int16);
    *(uint16_t *)d->value = value;
}
void vfd_float(setting_id_t id, float value)
{
    const setting_detail_t *d = detail(id);
    CHECK(d->datatype == Format_Decimal);
    *(float *)d->value = value;
}
void vfd_expect(unsigned index, uint8_t function, uint16_t reg, uint16_t value, bool blocking)
{
    CHECK(index < vfd_requests);
    const modbus_message_t *m = &vfd_messages[index];
    CHECK(m->adu[0] == 1 && m->adu[1] == function);
    CHECK(((m->adu[2] << 8) | m->adu[3]) == reg);
    CHECK(((m->adu[4] << 8) | m->adu[5]) == value);
    CHECK(vfd_blocking[index] == blocking);
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
bool task_add_delayed(foreground_task_ptr fn, void *data, uint32_t delay_ms)
{
    (void)fn;
    (void)data;
    (void)delay_ms;
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

bool task_run_on_reset(foreground_task_ptr fn, void *data) { return task_add_immediate(fn, data); }
