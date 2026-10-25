#include "plasma_host.h"

#include "grbl/state_machine.h"
unsigned plasma_waits, plasma_torch_starts, plasma_torch_stops, plasma_holds, plasma_resets,
    plasma_claims, plasma_releases;
bool plasma_torch_on, plasma_motor_claimed, plasma_wait_ok = true;
unsigned plasma_fail_waits;
sys_state_t plasma_state = STATE_IDLE;
spindle_ptrs_t *plasma_motor;
static struct
{
    foreground_task_ptr fn;
    void *data;
    uint64_t due;
} pending[16];
static foreground_task_ptr systick;
static void *systick_data;
static void reset(void) { plasma_resets++; }
static void prior_reset(void) {}
static void pulse(stepper_t *stepper) { CHECK(stepper && stepper->exec_segment); }
static void enable(axes_signals_t axes, bool hold)
{
    (void)hold;
    CHECK(!(axes.mask & ~AXES_BITMASK));
}
static void claim(uint_fast8_t axis, bool on)
{
    CHECK(axis == Z_AXIS);
    plasma_motor_claimed = on;
    if (on)
        plasma_claims++;
    else
        plasma_releases++;
}
static uint32_t elapsed(void) { return (uint32_t)(plasma_micros / 1000); }
static void delay(uint32_t ms, delay_callback_ptr callback)
{
    CHECK(!callback);
    plasma_micros += (uint64_t)ms * 1000;
}
static void bits(volatile uint_fast16_t *value, uint_fast16_t mask) { *value |= mask; }
static void rt(uint_fast16_t state) { CHECK(state == plasma_state); }
static void report(stream_write_ptr write, report_tracking_flags_t flags)
{
    (void)flags;
    write("|Previous:1");
}
static void selected(spindle_ptrs_t *spindle) { CHECK(spindle); }
static void torch(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    CHECK(spindle == plasma_motor && rpm >= 0);
    plasma_torch_on = state.on;
    if (state.on)
        plasma_torch_starts++;
    else
        plasma_torch_stops++;
}
static spindle_state_t torch_state(spindle_ptrs_t *spindle)
{
    CHECK(spindle);
    return (spindle_state_t){.on = plasma_torch_on};
}
bool settings_add_spindle_type(const char *name)
{
    CHECK(name && *name);
    return true;
}
void report_add_realtime(report_tracking_t report)
{
    (void)report;
    CHECK(false);
}
void gc_spindle_off(void) { CHECK(false); }
void system_raise_alarm(alarm_code_t alarm)
{
    (void)alarm;
    CHECK(false);
}
void st_rpm_changed(float rpm)
{
    (void)rpm;
    CHECK(false);
}
void plasma_runtime_prepare(void)
{
    hal.driver_reset = reset;
    hal.stepper.pulse_start = pulse;
    hal.stepper.enable = enable;
    hal.stepper.claim_motor = claim;
    hal.get_elapsed_ticks = elapsed;
    hal.delay_ms = delay;
    hal.set_bits_atomic = bits;
    grbl.on_reset = prior_reset;
    grbl.on_execute_realtime = rt;
    grbl.on_realtime_report = report;
    grbl.on_spindle_selected = selected;
    sys.override.feed_rate = sys.override.rapid_rate = 100;
    settings.pwm_spindle.rpm_max = 1000;
}
void plasma_set(setting_id_t id, float value)
{
    CHECK(plasma_details);
    for (unsigned i = 0; i < plasma_details->n_settings; i++)
    {
        const setting_detail_t *d = &plasma_details->settings[i];
        if (d->id != id)
            continue;
        CHECK(d->type == Setting_NonCore);
        if (d->datatype == Format_Decimal)
            *(float *)d->value = value;
        else if (d->datatype == Format_RadioButtons || d->datatype == Format_Int8 ||
                 d->datatype == Format_Bitfield)
            *(uint8_t *)d->value = (uint8_t)value;
        else
            CHECK(false);
        return;
    }
    CHECK(false);
}
void plasma_set_port(setting_id_t id, float value)
{
    CHECK(plasma_details);
    for (unsigned i = 0; i < plasma_details->n_settings; i++)
    {
        const setting_detail_t *detail = &plasma_details->settings[i];
        if (detail->id == id)
        {
            CHECK(detail->type == Setting_NonCoreFn && detail->datatype == Format_Decimal);
            CHECK(((setting_set_float_ptr)detail->value)(id, value) == Status_OK);
            return;
        }
    }
    CHECK(false);
}
int32_t plasma_wait_input(uint8_t port, wait_mode_t mode, float timeout)
{
    CHECK(port < 3);
    if (mode == WaitMode_High)
    {
        plasma_waits++;
        CHECK(timeout > 0);
        if (!plasma_wait_ok || plasma_fail_waits)
        {
            if (plasma_fail_waits)
                plasma_fail_waits--;
            plasma_micros += (uint64_t)(timeout * 1000000);
            return -1;
        }
        plasma_inputs[port] = 1;
        return 1;
    }
    return plasma_inputs[port] ? 1 : 0;
}
bool task_add_systick(foreground_task_ptr fn, void *data)
{
    CHECK(!systick && fn);
    systick = fn;
    systick_data = data;
    return true;
}
bool task_add_delayed(foreground_task_ptr fn, void *data, uint32_t delay_ms)
{
    CHECK(fn);
    for (unsigned i = 0; i < 16; i++)
        if (!pending[i].fn)
        {
            pending[i].fn = fn;
            pending[i].data = data;
            pending[i].due = plasma_micros + (uint64_t)delay_ms * 1000;
            return true;
        }
    CHECK(false);
    return false;
}
void task_delete(foreground_task_ptr fn, void *data)
{
    for (unsigned i = 0; i < 16; i++)
        if (pending[i].fn == fn && pending[i].data == data)
            pending[i].fn = NULL;
}
sys_state_t state_get(void) { return plasma_state; }
// shortcut: observe hold requests here; use full CORE suspension for planner integration tests.
bool protocol_execute_realtime(void)
{
    if (sys.rt_exec_state & EXEC_FEED_HOLD)
    {
        sys.rt_exec_state &= ~EXEC_FEED_HOLD;
        plasma_holds++;
        plasma_state = STATE_HOLD;
    }
    return true;
}
void plasma_tick(unsigned ms)
{
    for (unsigned n = 0; n < ms; n++)
    {
        plasma_micros += 1000;
        for (unsigned i = 0; i < 16; i++)
            if (pending[i].fn && pending[i].due <= plasma_micros)
            {
                foreground_task_ptr fn = pending[i].fn;
                void *data = pending[i].data;
                pending[i].fn = NULL;
                fn(data);
            }
        if (systick)
            systick(systick_data);
        if (grbl.on_execute_realtime)
            grbl.on_execute_realtime(plasma_state);
    }
}
void plasma_feed(float programmed, float actual)
{
    static uint8_t id;
    st_block_t block = {.programmed_rate = programmed};
    segment_t segment = {.id = ++id, .current_rate = actual};
    stepper_t stepper = {.new_block = true, .exec_block = &block, .exec_segment = &segment};
    hal.stepper.pulse_start(&stepper);
}
void plasma_boot(void)
{
    plasma_prepare(3, true);
    FILE *f = fopen("plasma.nvs", "rb");
    CHECK(f && fread(memory, 1, 16384, f) == 16384);
    CHECK(!fclose(f));
    plasma_load();
    for (unsigned i = 0; i < 3; i++)
        plasma_inputs[i] = 0;
    plasma_input("Arc ok", true);
    if (plasma_details->on_changed)
        plasma_details->on_changed(&settings, (settings_changed_flags_t){0});
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    static const spindle_ptrs_t spindle = {
        .type = SpindleType_Basic, .set_state = torch, .get_state = torch_state};
    CHECK(spindle_register(&spindle, "Host plasma") == 0 && spindle_select(0));
    plasma_motor = spindle_get(0);
    CHECK(plasma_motor && plasma_motor->cap.torch && systick);
}

const setting_detail_t *setting_get_details(setting_id_t id, setting_details_t **set)
{
    (void)id;
    (void)set;
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
