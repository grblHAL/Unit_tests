#pragma once
#include "support/motion_program_host.h"

typedef enum { Reset_Clearance, Reset_Positioning, Reset_Drilling, Reset_Retracting } drill_reset_phase_t;
static drill_reset_phase_t reset_phase;
static unsigned services, resets;
static bool reset_sent;
static bool drilled_below_surface;
static bool drill_prefill_motion;
static unsigned drill_planner_slots_to_leave;
static int32_t reset_position[N_AXIS];
static control_signals_t reset_controls(void) { return (control_signals_t){0}; }
static bool reset_connected(void) { return true; }
static void reset_coolant(coolant_state_t state) { CHECK(state.mask == 0); }
static void reset_driver(void)
{
    resets++;
    memcpy(reset_position, physical_position, sizeof(reset_position));
}
static void service_reset_drill(sys_state_t state)
{
    CHECK(++services < 200000);
    if(state == STATE_CYCLE) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
        if(physical_position[Z_AXIS] <= -20) drilled_below_surface = true;
        bool reached = reset_phase == Reset_Clearance ? physical_position[Z_AXIS] >= 40
                     : reset_phase == Reset_Positioning ? physical_position[X_AXIS] >= 40
                     : reset_phase == Reset_Drilling ? physical_position[Z_AXIS] <= -20
                     : drilled_below_surface && physical_position[Z_AXIS] >= 0;
        if(!reset_sent && reached) {
            reset_sent = true;
            CHECK(protocol_enqueue_realtime_command(CMD_RESET));
        }
    }
}
static inline void run_reset_drilling_program(drill_reset_phase_t phase, const char *text)
{
    prepare_motion_program();
    reset_phase = phase;
    hal.control.get_state = reset_controls;
    hal.stream.is_connected = reset_connected;
    hal.coolant.set_state = reset_coolant;
    hal.driver_reset = reset_driver;
    grbl.on_execute_realtime = grbl.on_execute_delay = service_reset_drill;
    for(unsigned axis = 0; axis < N_AXIS; axis++) settings.axis[axis].acceleration = 36000;
    if(drill_prefill_motion)
        while(plan_get_block_buffer_available() > drill_planner_slots_to_leave)
            queue_motion_program("G91G1X1F100");
    char program[96];
    CHECK(strlen(text) < sizeof(program));
    strcpy(program, text);
    CHECK(gc_execute_block(program) == Status_OK);
    CHECK(reset_sent && sys.abort && sys.position_lost && resets == 1);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(physical_position[axis] == reset_position[axis]);
        CHECK(sys.position[axis] == physical_position[axis]);
    }
    CHECK(axis_pulses[Y_AXIS] == 0);
    CHECK(physical_position[X_AXIS] <= 80);
}
static inline void run_reset_drilling(drill_reset_phase_t phase)
{
    run_reset_drilling_program(phase, "G91G81X1Z-5R2L20F100");
}
