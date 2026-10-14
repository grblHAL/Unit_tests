#pragma once
#include "support/parking_host.h"
static spindle_state_t parking_spindle_state;
static float parking_spindle_rpm;
static int32_t parking_spindle_on_z, parking_spindle_off_z, parking_coolant_on_z, parking_coolant_off_z;
static unsigned parking_coolant_off_calls;
static bool parking_reopen_on_restore;
static void parking_spindle_set(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    CHECK(spindle == spindle_get(0));
    parking_spindle_state = state;
    parking_spindle_rpm = rpm;
    if(state.on) parking_spindle_on_z = physical_position[Z_AXIS];
    else parking_spindle_off_z = physical_position[Z_AXIS];
    /* A door input arriving during spindle spin-up is queued as a real event. */
    if(parking_reopen_on_restore && state.on && state_get() == STATE_SAFETY_DOOR) {
        parking_reopen_on_restore = false;
        parking_door_open = true;
        control_interrupt_handler((control_signals_t){.safety_door_ajar = true});
    }
}
static spindle_state_t parking_spindle_get(spindle_ptrs_t *spindle)
{
    CHECK(spindle == spindle_get(0));
    return parking_spindle_state;
}
static void parking_coolant_record(coolant_state_t state)
{
    parking_coolant = state;
    if(state.flood) parking_coolant_on_z = physical_position[Z_AXIS];
    else {
        parking_coolant_off_calls++;
        parking_coolant_off_z = physical_position[Z_AXIS];
    }
}
static inline void start_powered_parking_move(bool keep_coolant)
{
    prepare_parking_move();
    hal.coolant.set_state = parking_coolant_record;
    hal.coolant_cap.flood = true;
    hal.signals_cap.safety_door_ajar = true;
    spindle_ptrs_t *spindle = spindle_get(0);
    spindle->cap.variable = true;
    spindle->rpm_min = 100;
    spindle->rpm_max = 12000;
    spindle->set_state = parking_spindle_set;
    spindle->get_state = parking_spindle_get;
    settings.safety_door.flags.keep_coolant_on = keep_coolant;
    char spindle_command[] = "M3S5000", coolant_command[] = "M8";
    CHECK(gc_execute_block(spindle_command) == Status_OK);
    CHECK(gc_execute_block(coolant_command) == Status_OK);
    CHECK(parking_spindle_state.on && parking_coolant.flood);
    begin_parking_move();
}
static inline void close_and_resume_parking(void)
{
    parking_door_open = false;
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
}
static inline void finish_powered_parking(void)
{
    for(unsigned ticks = 0; ticks < 200000 && state_get() != STATE_IDLE; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
        CHECK(protocol_exec_rt_system());
    }
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(sys.position[X_AXIS] == 1600 && physical_position[X_AXIS] == 1600);
    CHECK(sys.position[Z_AXIS] == -800 && physical_position[Z_AXIS] == -800);
    CHECK(axis_pulses[X_AXIS] == 1600);
}
