#pragma once
#include "support/motion_program_host.h"
static bool parking_door_open;
static coolant_state_t parking_coolant;
static control_signals_t parking_controls(void) { return (control_signals_t){.safety_door_ajar = parking_door_open}; }
static coolant_state_t parking_get_coolant(void) { return parking_coolant; }
static void parking_set_coolant(coolant_state_t state) { parking_coolant = state; }
static message_code_t parking_feedback(message_code_t message) { return message; }
static inline void start_parking_move(void)
{
    prepare_motion_program();
    hal.control.get_state = parking_controls;
    hal.coolant.get_state = parking_get_coolant;
    hal.coolant.set_state = parking_set_coolant;
    grbl.report.feedback_message = parking_feedback;
    settings.parking.flags.enabled = true;
    settings.parking.axis = Z_AXIS;
    settings.parking.target = -2;
    settings.parking.pullout_increment = 2;
    settings.parking.pullout_rate = 100;
    settings.parking.rate = 500;
    sys.homed.mask = 1u << Z_AXIS;
    sys.position[Z_AXIS] = physical_position[Z_AXIS] = -800;
    gc_sync_position();
    plan_sync_position();
    queue_motion_program("G1X20F100");
    state_set(STATE_CYCLE);
    for(unsigned ticks = 0; ticks < 100; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
}
static inline void park_until_retracted(void)
{
    parking_door_open = true;
    CHECK(protocol_enqueue_realtime_command(CMD_SAFETY_DOOR));
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_SAFETY_DOOR);
    for(unsigned ticks = 0; ticks < 200000 && sys.parking_state != Parking_DoorAjar; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
        CHECK(protocol_exec_rt_system());
    }
    CHECK(sys.parking_state == Parking_DoorAjar);
    CHECK(!sys.step_control.execute_sys_motion);
}
