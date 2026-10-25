#include "support/canned_motion_host.h"

int main(void)
{
    prepare_canned_motion();
    char rotary[] = "1", wrap[] = "1";
    CHECK(settings_store_setting(Settings_RotaryAxes, rotary) == Status_OK);
    CHECK(settings_store_setting(Setting_RotaryWrap, wrap) == Status_OK);
    execute_canned("G90G0A10");
    execute_canned("G28.1");
    execute_canned("G0A90");
    unsigned before = axis_pulses[A_AXIS];
    execute_canned("G90G28A0");
    CHECK(axis_pulses[A_AXIS] - before == 100 * 80);
    CHECK(physical_position[A_AXIS] == 10 * 80 && sys.position[A_AXIS] == 10 * 80);
    NEAR(gc_state.position[A_AXIS], 10);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        if(axis != A_AXIS) CHECK(axis_pulses[axis] == 0);
    CHECK(!gc_state.modal.distance_incremental && !sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
