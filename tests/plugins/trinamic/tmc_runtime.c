#include "tmc_host.h"

#include "grbl/state_machine.h"
sys_state_t tmc_state = STATE_IDLE;
unsigned tmc_enable_calls, tmc_pulse_calls, tmc_holds, tmc_warn_reports;
static struct
{
    foreground_task_ptr fn;
    void *data;
    uint64_t due;
} tasks[32];
static uint64_t now;
static bool enqueue(foreground_task_ptr fn, void *data, uint32_t delay)
{
    CHECK(fn);
    for (unsigned i = 0; i < 32; i++)
        if (!tasks[i].fn)
        {
            tasks[i].fn = fn;
            tasks[i].data = data;
            tasks[i].due = now + delay;
            return true;
        }
    CHECK(false);
    return false;
}
bool task_add_immediate(foreground_task_ptr fn, void *data)
{
    if (fn == report_warning)
    {
        CHECK(data);
        tmc_warnings++;
    }
    return enqueue(fn, data, 0);
}
bool task_add_delayed(foreground_task_ptr fn, void *data, uint32_t delay)
{
    return enqueue(fn, data, delay);
}
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    return task_add_immediate(fn, data);
}
void task_delete(foreground_task_ptr fn, void *data)
{
    for (unsigned i = 0; i < 32; i++)
        if (tasks[i].fn == fn && tasks[i].data == data)
            tasks[i].fn = NULL;
}
void tmc_run_tasks(void)
{
    for (unsigned count = 0; count < 64; count++)
    {
        bool ran = false;
        for (unsigned i = 0; i < 32; i++)
            if (tasks[i].fn && tasks[i].due <= now)
            {
                foreground_task_ptr fn = tasks[i].fn;
                void *data = tasks[i].data;
                tasks[i].fn = NULL;
                fn(data);
                ran = true;
            }
        if (!ran)
            return;
    }
    CHECK(false);
}
void tmc_poll(void)
{
    now += 250;
    tmc_run_tasks();
}
sys_state_t state_get(void) { return tmc_state; }
static void enable(axes_signals_t axes, bool hold)
{
    CHECK((axes.mask & ~AXES_BITMASK) == 0);
    (void)hold;
    tmc_enable_calls++;
}
static void pulse(stepper_t *stepper)
{
    CHECK(stepper);
    tmc_pulse_calls++;
}
static bool realtime(uint8_t command)
{
    CHECK(command == CMD_FEED_HOLD);
    tmc_holds++;
    return true;
}
void report_message(const char *message, message_type_t type)
{
    CHECK(type == Message_Warning && strstr(message, "Over-Temperature Motor: "));
    tmc_warn_reports++;
    CHECK(strlen(tmc_output) + strlen(message) < sizeof(tmc_output));
    strcat(tmc_output, message);
}
void st_go_idle(void) { CHECK(false); }
void st_wake_up(void) { CHECK(false); }
void tmc_runtime_prepare(void)
{
    hal.stepper.enable = enable;
    hal.stepper.pulse_start = pulse;
    grbl.enqueue_realtime_command = realtime;
}
void tmc_block(unsigned axis)
{
    CHECK(axis < N_AXIS);
    st_block_t next_block = {0};
    segment_t next_segment = {.exec_block = &next_block};
    segment_t segment = {.next = &next_segment};
    stepper_t stepper = {.new_block = true, .exec_segment = &segment};
    stepper.steps.value[axis] = 1;
    hal.stepper.pulse_start(&stepper);
    tmc_run_tasks();
}
void tmc_mask(setting_id_t id, uint8_t value)
{
    for (unsigned i = 0; i < tmc_settings->n_settings; i++)
    {
        const setting_detail_t *d = &tmc_settings->settings[i];
        if (d->id == id)
        {
            CHECK(d->type == Setting_NonCore && d->datatype == Format_AxisMask);
            *(uint8_t *)d->value = value;
            return;
        }
    }
    CHECK(false);
}
void tmc_sensitivity(setting_id_t base, unsigned axis, float value)
{
    for (unsigned i = 0; i < tmc_settings->n_settings; i++)
    {
        const setting_detail_t *d = &tmc_settings->settings[i];
        if (d->id == base)
        {
            CHECK(d->datatype == Format_Decimal);
            CHECK(((setting_set_float_ptr)d->value)(base + axis, value) == Status_OK);
            return;
        }
    }
    CHECK(false);
}
