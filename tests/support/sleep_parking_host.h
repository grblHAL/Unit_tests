#pragma once
#include "support/sleep_wait_host.h"
#include "support/parking_host.h"
static bool entered_parking_sleep, parking_sleep_coolant_off;
static void observe_parking_sleep_coolant(coolant_state_t state)
{
    if(!state.value) {
        CHECK(physical_position[Z_AXIS] == -160);
        parking_sleep_coolant_off = true;
    }
    parking_set_coolant(state);
}
static message_code_t observe_parking_sleep(message_code_t message)
{
    if(message == Message_SleepMode)
        entered_parking_sleep = true;
    return message;
}
static inline void prepare_sleep_parking(void)
{
    prepare_parking_move();
    hal.coolant.set_state = observe_parking_sleep_coolant;
    settings.flags.sleep_enable = true;
    settings.safety_door.flags.keep_coolant_on = true;
    hal.stream.is_connected = sleep_connected;
    hal.stream.get_rx_buffer_free = sleep_rx_free;
    engine_ticks = 100;
    grbl.report.feedback_message = observe_parking_sleep;
    char coolant[] = "M8";
    CHECK(gc_execute_block(coolant) == Status_OK);
    CHECK(parking_coolant.flood);
}
static inline void finish_sleep_parking(void)
{
    for(unsigned ticks = 0; ticks < 200000 && !entered_parking_sleep; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
        CHECK(protocol_exec_rt_system());
    }
    CHECK(entered_parking_sleep && state_get() == STATE_SLEEP);
    CHECK(parking_sleep_coolant_off && !parking_coolant.flood && !parking_coolant.mist);
    CHECK(physical_position[Z_AXIS] == -160 && sys.position[Z_AXIS] == -160);
    CHECK(axis_pulses[Z_AXIS] == 640);
    CHECK(!sys.step_control.execute_sys_motion);
}
