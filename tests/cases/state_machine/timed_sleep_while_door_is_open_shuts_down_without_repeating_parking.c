#include "support/sleep_parking_host.h"
#include "check.h"

int main(void)
{
    prepare_sleep_parking();
    begin_parking_move();
    park_until_retracted();
    CHECK(parking_coolant.flood);
    int32_t stopped_x = physical_position[X_AXIS];
    unsigned stopped_x_pulses = axis_pulses[X_AXIS];
    unsigned parked_z_pulses = axis_pulses[Z_AXIS];
    wait_for_sleep();
    CHECK(sleep_wait_calls == 1 && (sys.rt_exec_state & EXEC_SLEEP));
    grbl.on_execute_realtime = protocol_execute_noop;
    finish_sleep_parking();
    CHECK(parking_door_open);
    CHECK(physical_position[X_AXIS] == stopped_x && axis_pulses[X_AXIS] == stopped_x_pulses);
    CHECK(axis_pulses[Z_AXIS] == parked_z_pulses);
    return EXIT_SUCCESS;
}
