#include "support/parking_host.h"

static bool reset_during_restore, reset_delivered;
static unsigned driver_reset_calls;
static void reset_driver(void) { driver_reset_calls++; }
static void reset_input(void) {}
static void service_restore_delay(uint32_t milliseconds, void (*callback)(void))
{
    engine_ticks += milliseconds;
    if(reset_during_restore && parking_coolant.flood && state_get() == STATE_SAFETY_DOOR) {
        reset_during_restore = false;
        reset_delivered = true;
        CHECK(protocol_enqueue_realtime_command(CMD_RESET));
    }
    if(callback) callback();
}
int main(void)
{
    prepare_parking_move();
    hal.driver_reset = reset_driver;
    hal.stream.reset_read_buffer = reset_input;
    hal.coolant_cap.flood = true;
    hal.signals_cap.safety_door_ajar = true;
    hal.delay_ms = service_restore_delay;
    char coolant[] = "M8";
    CHECK(gc_execute_block(coolant) == Status_OK && parking_coolant.flood);
    begin_parking_move();
    park_until_retracted();
    CHECK(!parking_coolant.flood);
    int32_t stopped_x = physical_position[X_AXIS];
    settings.safety_door.coolant_on_delay = 0.1f;
    reset_during_restore = true;
    parking_door_open = false;
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    for(unsigned tick = 0; tick < 200000 && !sys.abort; tick++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
        if(!protocol_exec_rt_system()) break;
    }
    CHECK(reset_delivered && !reset_during_restore);
    CHECK(driver_reset_calls == 1);
    CHECK(sys.abort);
    CHECK(physical_position[X_AXIS] == stopped_x);
    CHECK(physical_position[Z_AXIS] == -640);
    CHECK(sys.position[Z_AXIS] == -640);
    return EXIT_SUCCESS;
}
