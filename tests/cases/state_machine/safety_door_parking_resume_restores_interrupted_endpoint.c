#include "support/parking_host.h"
#include "check.h"

int main(void)
{
    start_parking_move();
    park_until_retracted();
    parking_door_open = false;
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    for(unsigned ticks = 0; ticks < 200000 && state_get() != STATE_IDLE; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
        CHECK(protocol_exec_rt_system());
    }
    CHECK(state_get() == STATE_IDLE);
    CHECK(plan_get_current_block() == NULL);
    CHECK(sys.position[X_AXIS] == 1600);
    CHECK(physical_position[X_AXIS] == 1600);
    CHECK(sys.position[Z_AXIS] == -800);
    CHECK(physical_position[Z_AXIS] == -800);
    CHECK(axis_pulses[X_AXIS] == 1600);
    CHECK(axis_pulses[Z_AXIS] == 1280);
    return EXIT_SUCCESS;
}
