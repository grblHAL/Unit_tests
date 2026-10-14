#pragma once
#include "support/engine_host.h"
#include "protocol.h"
#include "grbllib.h"
#include "state_machine.h"
#include "nvs.h"
#include "check.h"
#include <string.h>
static unsigned boot_reads, boot_read_calls, boot_setup_calls, boot_release_calls;
static const char *boot_program = "$G\n";
static bool boot_setup_success = true, boot_init_success = true;
static bool boot_force_alarm, boot_homing_required, boot_check_limits, boot_sleep_enabled;
static bool boot_observe_fault_loop;
static uint16_t boot_idle_lock_time;
static axes_signals_t boot_enabled_axes;
static coolant_state_t boot_coolant_state;
static bool boot_coolant_seen_on;
static limit_signals_t boot_limit_signals;
static control_signals_t boot_control_signals;
static void (*boot_before_read)(void);
static on_execute_realtime_ptr boot_on_realtime, boot_core_realtime;
static unsigned boot_realtime_calls;
static inline void service_boot_events(sys_state_t state)
{
    CHECK(++boot_realtime_calls < 100000);
    boot_core_realtime(state);
    if(boot_on_realtime) boot_on_realtime(state);
}
static bool boot_keep_feed_override, boot_keep_rapid_override;
static unsigned boot_feed_before_reset, boot_rapid_before_reset;
static bool boot_pulse_delay_capability = true;
static bool boot_restore_position;
static int32_t boot_hardware_position[N_AXIS];
static unsigned boot_position_calls;
static inline bool restore_position(int32_t (*position)[N_AXIS])
{
    memcpy(*position, boot_hardware_position, sizeof(boot_hardware_position));
    boot_position_calls++;
    return true;
}
static const char *boot_startup_program = "";
static void (*boot_during_setup)(settings_t *settings);
static void (*boot_during_init)(void);
static uint8_t boot_spindle_reference;
static bool setup(settings_t *s) { CHECK(s == &settings); boot_setup_calls++; if(boot_during_setup) boot_during_setup(s); return boot_setup_success; }
static bool release_driver(void) { boot_release_calls++; return false; }
static control_signals_t controls(void) { return boot_control_signals; }
static limit_signals_t limits(void) { return boot_limit_signals; }
static void enable_limits(bool on, axes_signals_t homing) { (void)on; (void)homing; }
static void enable_steps(axes_signals_t axes, bool hold) { boot_enabled_axes = axes; (void)hold; }
static void idle(bool clear) { (void)clear; }
static void wake(void) { CHECK(false); }
static void cycles(uint32_t n) { CHECK(n > 0); }
static void pulse(stepper_t *s) { (void)s; CHECK(false); }
static void coolant_set(coolant_state_t s) { boot_coolant_state = s; boot_coolant_seen_on |= s.mask != 0; }
static coolant_state_t coolant_get(void) { return boot_coolant_state; }
static void reset_read(void) { }
static uint16_t count(void) { return 0; }
static bool connected(void) { return true; }
static bool write_char(uint8_t c) { char s[2] = {(char)c, 0}; hal.stream.write(s); return true; }
static int32_t read_char(void)
{
    CHECK(++boot_read_calls < 1000);
    if(boot_before_read) boot_before_read();
    if(boot_program[boot_reads]) {
        uint8_t c = (uint8_t)boot_program[boot_reads++];
        if(c == CMD_RESET) {
            boot_feed_before_reset = sys.override.feed_rate;
            boot_rapid_before_reset = sys.override.rapid_rate;
        }
        if((c == CMD_RESET || c >= 0x80) && protocol_enqueue_realtime_command(c))
            return SERIAL_NO_DATA;
        return c;
    }
    if(!boot_observe_fault_loop)
        protocol_enqueue_realtime_command(CMD_EXIT);
    return SERIAL_NO_DATA;
}
/* Wrap the board entry point only; all core initialization remains real. */
bool __wrap_driver_init(void)
{
    grbl_t core_grbl = grbl; system_t core_sys = sys; grbl_hal_t core_hal = hal;
    engine_prepare(); grbl = core_grbl; sys = core_sys;
    if(boot_on_realtime) {
        boot_core_realtime = grbl.on_execute_realtime;
        grbl.on_execute_realtime = service_boot_events;
    }
    hal.version = core_hal.version; hal.driver_reset = core_hal.driver_reset;
    hal.irq_claim = core_hal.irq_claim;
    hal.nvs.size = core_hal.nvs.size; hal.step_us_min = core_hal.step_us_min;
    hal.tool.atc_get_state = core_hal.tool.atc_get_state;
    hal.control.interrupt_callback = core_hal.control.interrupt_callback;
    hal.limits.interrupt_callback = core_hal.limits.interrupt_callback;
    hal.stepper.interrupt_callback = core_hal.stepper.interrupt_callback;
    hal.stream_blocking_callback = core_hal.stream_blocking_callback;
    hal.coolant_cap = core_hal.coolant_cap;
    if(boot_restore_position) hal.get_position = restore_position;
    hal.driver_cap.step_pulse_delay = boot_pulse_delay_capability; hal.driver_setup = setup; hal.driver_release = release_driver;
    hal.signals_cap.mask = boot_control_signals.mask;
    hal.limits_cap = boot_limit_signals;
    hal.control.get_state = controls; hal.limits.get_state = limits; hal.limits.enable = enable_limits;
    hal.f_step_timer = 1000000; hal.stepper.enable = enable_steps; hal.stepper.go_idle = idle;
    hal.stepper.wake_up = wake; hal.stepper.cycles_per_tick = cycles; hal.stepper.pulse_start = pulse;
    hal.coolant.set_state = coolant_set; hal.coolant.get_state = coolant_get;
    hal.stream.read = read_char; hal.stream.reset_read_buffer = reset_read; hal.stream.get_tx_buffer_count = count;
    hal.stream.get_rx_buffer_free = count; hal.stream.is_connected = connected; hal.stream.write_char = write_char;
    settings.spindle.ref_id = boot_spindle_reference;
    settings.flags.force_initialization_alarm = boot_force_alarm;
    settings.flags.sleep_enable = boot_sleep_enabled;
    settings.steppers.idle_lock_time = boot_idle_lock_time;
    settings.limits.flags.hard_enabled = boot_check_limits;
    settings.limits.flags.check_at_init = boot_check_limits;
    if(boot_homing_required) {
        settings.homing.flags.enabled = true;
        settings.homing.flags.init_lock = true;
        settings.homing.cycle[0].mask = AXES_BITMASK;
    }
    settings.flags.keep_feed_override_on_reset = boot_keep_feed_override;
    settings.flags.keep_rapids_override_on_reset = boot_keep_rapid_override;
    settings.version.id = SETTINGS_VERSION; settings.version.build = GRBL_BUILD - 20000000UL;
    hal.nvs.put_byte(0, SETTINGS_VERSION); settings_write_global();
    coord_system_data_t coordinates = {0}; for(unsigned i = 0; i < N_CoordinateSystems; i++) settings_write_coord_data((coord_system_id_t)i, &coordinates);
    stored_line_t empty = {0}; for(unsigned i = 0; i < N_STARTUP_LINE; i++) settings_write_startup_line(i, empty);
    settings_write_build_info(empty);
    stored_line_t startup = {0};
    CHECK(strlen(boot_startup_program) < sizeof(startup));
    strcpy(startup, boot_startup_program);
    settings_write_startup_line(0, startup);
    if(boot_during_init) boot_during_init();
    return boot_init_success;
}
