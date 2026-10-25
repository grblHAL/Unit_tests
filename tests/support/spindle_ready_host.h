#pragma once
#include "support/engine_host.h"
#include "spindle_control.h"
#include "state_machine.h"
#include "protocol.h"
#include "report.h"
#include "check.h"
#include <string.h>
static spindle_state_t ready_hardware;
static uint32_t ready_after_ms;
static unsigned ready_queries, ready_notifications;
static float ready_rpm;
static float ready_tolerance = 1;
static bool ready_connected(void) { return true; }
static control_signals_t ready_controls(void) { return (control_signals_t){0}; }
static void ready_output(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{ CHECK(spindle == spindle_get(0)); ready_hardware = state; ready_rpm = rpm; }
static spindle_state_t ready_input(spindle_ptrs_t *spindle)
{
    CHECK(spindle == spindle_get(0)); ready_queries++;
    spindle_state_t state = ready_hardware;
    state.at_speed = state.on && engine_ticks >= ready_after_ms;
    return state;
}
static void ready_notified(spindle_ptrs_t *spindle, spindle_state_t state)
{ CHECK(spindle == spindle_get(0)); CHECK(state.on); CHECK(engine_ticks >= ready_after_ms); ready_notifications++; }
static void ready_idle(bool clear) { (void)clear; }
static void ready_enable(axes_signals_t axes, bool hold) { (void)axes; (void)hold; }
static inline void prepare_spindle_ready_capabilities(uint32_t feedback_delay, uint32_t timeout, spindle_cap_t capabilities)
{
    engine_prepare(); sys.cold_start = true;
    static spindle_ptrs_t driver = {.type = SpindleType_Basic, .ref_id = 1,
        .rpm_min = 1000, .rpm_max = 12000, .at_speed_tolerance = 1,
        .cap = {.direction = true, .variable = true, .rpm_range_locked = true, .at_speed = true},
        .set_state = ready_output, .get_state = ready_input};
    driver.cap = capabilities;
    driver.at_speed_tolerance = ready_tolerance;
    CHECK(spindle_register(&driver, "Ready feedback") == 0);
    settings.spindle.at_speed_tolerance = ready_tolerance; settings.spindle.on_delay = timeout;
    CHECK(spindle_select(0));
    coord_system_data_t coordinates = {0};
    for(unsigned id = 0; id < N_CoordinateSystems; id++)
        settings_write_coord_data((coord_system_id_t)id, &coordinates);
    gc_init(false); CHECK(plan_reset()); limits_init();
    hal.control.get_state = ready_controls; hal.stream.is_connected = ready_connected;
    hal.stepper.go_idle = ready_idle; hal.stepper.enable = ready_enable;
    grbl.on_execute_realtime = protocol_execute_noop;
    grbl.on_spindle_at_speed = ready_notified;
    report_init_fns(); report_init(); state_set(STATE_IDLE);
    sys.cold_start = false; sys.driver_started = true;
    ready_after_ms = feedback_delay; engine_ticks = ready_queries = 0;
}
static inline void prepare_spindle_ready(uint32_t feedback_delay, uint32_t timeout)
{
    prepare_spindle_ready_capabilities(feedback_delay, timeout,
        (spindle_cap_t){.direction = true, .variable = true, .rpm_range_locked = true, .at_speed = true});
}
static inline status_code_t ready_block(const char *text)
{ char block[64]; CHECK(strlen(text) < sizeof(block)); strcpy(block, text); return gc_execute_block(block); }
