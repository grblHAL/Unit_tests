#pragma once
#include "support/hold_host.h"
#include "sleep.h"
static coolant_state_t sleep_coolant_output;
static bool sleep_door_open, sleep_input_arrives;
static unsigned sleep_wait_calls;
static uint16_t sleep_free_space = 100;
static coolant_state_t sleep_get_coolant(void) { return sleep_coolant_output; }
static void sleep_set_coolant(coolant_state_t state) { sleep_coolant_output = state; }
static control_signals_t sleep_controls(void) { return (control_signals_t){.safety_door_ajar = sleep_door_open}; }
static bool sleep_connected(void) { return true; }
static uint16_t sleep_rx_free(void) { return sleep_free_space; }
static void service_sleep_wait(sys_state_t state)
{
    CHECK(++sleep_wait_calls < 10);
    if(sleep_input_arrives)
        sleep_free_space--;
    else {
        engine_ticks += (uint32_t)(SLEEP_DURATION * 60000) + 1;
        engine_execute_tasks(state);
    }
}
static inline void prepare_sleep_workflow(void)
{
    prepare_motion_program();
    settings.flags.sleep_enable = true;
    hal.coolant.set_state = sleep_set_coolant;
    hal.coolant.get_state = sleep_get_coolant;
    hal.control.get_state = sleep_controls;
    hal.stream.is_connected = sleep_connected;
    hal.stream.get_rx_buffer_free = sleep_rx_free;
    char coolant[] = "M8";
    CHECK(gc_execute_block(coolant) == Status_OK);
    CHECK(sleep_coolant_output.flood);
    engine_ticks = 100;
}
static inline void start_sleep_cut(void)
{
    prepare_sleep_workflow();
    queue_motion_program("G1X20F100");
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    for(unsigned i = 0; i < 100; i++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
}
static inline void wait_for_sleep(void)
{
    grbl.on_execute_realtime = service_sleep_wait;
    sleep_check();
}
