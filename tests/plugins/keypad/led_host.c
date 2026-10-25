#include "led_host.h"
grbl_hal_t hal;
grbl_t grbl;
bool led_bus_ok = true, led_probe_ok = true, led_send_ok = true;
unsigned led_probes, led_warnings, led_writes, led_states, led_selects;
unsigned led_spindles, led_coolants, led_reports, led_plugins;
uint8_t led_bytes[32][2];
bool led_blocking[32];
spindle_ptrs_t led_spindle;
spindle_state_t led_spindle_state;
coolant_state_t led_coolant_state;
i2c_cap_t i2c_start(void) { return (i2c_cap_t){.started = led_bus_ok}; }
bool i2c_probe(i2c_address_t address)
{
    CHECK(address == 0x20);
    led_probes++;
    return led_probe_ok;
}
bool i2c_send(i2c_address_t address, uint8_t *data, size_t size, bool block)
{
    CHECK(address == 0x20 && data && size == 2 && led_writes < 32);
    memcpy(led_bytes[led_writes], data, size);
    led_blocking[led_writes++] = block;
    return led_send_ok;
}
static void state_changed(sys_state_t state)
{
    (void)state;
    led_states++;
}
static bool spindle_selected(spindle_ptrs_t *spindle)
{
    CHECK(spindle == &led_spindle);
    led_selects++;
    return true;
}
static void spindle_set(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    CHECK(spindle == &led_spindle && rpm == 500);
    led_spindle_state = state;
    led_spindles++;
}
static void coolant_set(coolant_state_t state)
{
    led_coolant_state = state;
    led_coolants++;
}
static void report_options(bool newopt)
{
    (void)newopt;
    led_reports++;
}
void report_plugin(const char *name, const char *version)
{
    CHECK(!strcmp(name, "I2C LEDS") && !strcmp(version, "0.04"));
    led_plugins++;
}
void report_warning(void *message)
{
    CHECK(message && !strcmp(message, "I2C LEDs not connected!"));
    led_warnings++;
}
bool task_run_on_startup(foreground_task_ptr task, void *data)
{
    CHECK(task == report_warning);
    task(data);
    return true;
}
void led_prepare(void)
{
    hal.coolant.set_state = coolant_set;
    led_spindle.set_state = spindle_set;
    grbl.on_state_change = state_changed;
    grbl.on_spindle_select = spindle_selected;
    grbl.on_report_options = report_options;
}
