#include "support/canned_motion_host.h"

int main(void)
{
    prepare_canned_motion();
    char rotary[] = "1", wrap[] = "1";
    CHECK(settings_store_setting(Settings_RotaryAxes, rotary) == Status_OK);
    CHECK(settings_store_setting(Setting_RotaryWrap, wrap) == Status_OK);
    CHECK(settings.steppers.is_rotary.mask == (1u << A_AXIS));
    CHECK(settings.steppers.rotary_wrap.mask == (1u << A_AXIS));
    execute_canned("G90G0A30");
    execute_canned("G28.1");
    execute_canned("G0A90");
    CHECK(physical_position[A_AXIS] == 7200 && sys.position[A_AXIS] == 7200);
    unsigned before = axis_pulses[A_AXIS];
    execute_canned("G91G28A0");
    CHECK(axis_pulses[A_AXIS] - before == 4800);
    CHECK(physical_position[A_AXIS] == 2400 && sys.position[A_AXIS] == 2400);
    NEAR(gc_state.position[A_AXIS], 30);
    CHECK(gc_state.modal.distance_incremental);
    execute_canned("G90");
    CHECK(!gc_state.modal.distance_incremental);
    execute_canned("G0A90");
    before = axis_pulses[A_AXIS];
    execute_canned("G91G28A10");
    CHECK(axis_pulses[A_AXIS] - before == 6400);
    CHECK(physical_position[A_AXIS] == 2400 && sys.position[A_AXIS] == 2400);
    NEAR(gc_state.position[A_AXIS], 30);
    execute_canned("G90");
    CHECK(settings.steppers.rotary_wrap.mask == (1u << A_AXIS));
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        if(axis != A_AXIS) CHECK(axis_pulses[axis] == 0 && physical_position[axis] == 0);
    CHECK(plan_get_current_block() == NULL && state_get() == STATE_IDLE);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
