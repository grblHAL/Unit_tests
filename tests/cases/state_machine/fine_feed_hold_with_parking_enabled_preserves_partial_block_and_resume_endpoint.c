#include "support/hold_host.h"
int main(void)
{
    prepare_motion_program();
    char parking[] = "1";
    CHECK(settings_store_setting(Setting_ParkingEnable, parking) == Status_OK);
    CHECK(settings.parking.flags.enabled);
    queue_motion_program("G1X1F0.5");
    queue_motion_program("G1X2F0.5");
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    for(unsigned tick = 0; tick < 2000 && physical_position[X_AXIS] == 0; tick++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
    CHECK(state_get() == STATE_CYCLE && physical_position[X_AXIS] > 0 && physical_position[X_AXIS] < 80);
    hold_motion();
    int32_t stopped = physical_position[X_AXIS];
    CHECK(stopped > 0 && stopped < 80);
    for(unsigned tick = 0; tick < 4; tick++) {
        st_prep_buffer();
        CHECK(protocol_exec_rt_system());
        CHECK(physical_position[X_AXIS] == stopped);
    }
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    CHECK(axis_pulses[X_AXIS] == 160 && physical_position[X_AXIS] == 160);
    CHECK(sys.position[X_AXIS] == 160 && axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(!sys.suspend && !sys.abort);
    return EXIT_SUCCESS;
}
