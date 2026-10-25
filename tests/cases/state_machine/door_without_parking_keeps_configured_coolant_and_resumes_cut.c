#include "support/laser_stepper_host.h"
#include "support/parking_host.h"

int main(void)
{
    prepare_pwm_stepper_mode(Mode_Standard);
    configure_parking_move();
    settings.parking.flags.enabled = false;
    hal.signals_cap.safety_door_ajar = true;
    hal.coolant_cap.flood = true;
    settings.safety_door.flags.keep_coolant_on = true;
    sys.cold_start = false;
    sys.driver_started = true;
    CHECK(state_get() == STATE_IDLE && physical_position[Z_AXIS] == -800);
    unsigned z_pulses = axis_pulses[Z_AXIS];
    CHECK(laser_block("M3S500") == Status_OK);
    CHECK(laser_block("M8") == Status_OK);
    CHECK(laser_output_state.on && parking_coolant.flood);
    begin_parking_move();
    parking_door_open = true;
    control_interrupt_handler((control_signals_t){.safety_door_ajar = true});
    CHECK(protocol_exec_rt_system());
    for(unsigned tick = 0; tick < 200000 && sys.parking_state != Parking_DoorAjar; tick++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
        CHECK(protocol_exec_rt_system());
    }
    CHECK(state_get() == STATE_SAFETY_DOOR && sys.parking_state == Parking_DoorAjar);
    CHECK(!laser_output_state.on && parking_coolant.flood);
    CHECK(physical_position[Z_AXIS] == -800 && axis_pulses[Z_AXIS] == z_pulses);
    CHECK(plan_get_current_block() != NULL);
    parking_door_open = false;
    system_set_exec_state_flag(EXEC_DOOR_CLOSED);
    CHECK(protocol_exec_rt_system());
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    for(unsigned tick = 0; tick < 200000 && state_get() != STATE_IDLE; tick++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
        CHECK(protocol_exec_rt_system());
    }
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(physical_position[X_AXIS] == 1600 && axis_pulses[X_AXIS] == 1600);
    CHECK(physical_position[Z_AXIS] == -800 && axis_pulses[Z_AXIS] == z_pulses);
    CHECK(laser_output_state.on && parking_coolant.flood);
    return EXIT_SUCCESS;
}
