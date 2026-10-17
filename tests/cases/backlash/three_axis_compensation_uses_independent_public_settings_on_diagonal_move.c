#include "support/backlash_settings_host.h"
int main(void)
{
    prepare_motion_program();
    char x[] = "0.1", y[] = "0.05", z[] = "0.125";
    CHECK(settings_store_setting(Setting_AxisBacklash + X_AXIS, x) == Status_OK);
    CHECK(settings_store_setting(Setting_AxisBacklash + Y_AXIS, y) == Status_OK);
    CHECK(settings_store_setting(Setting_AxisBacklash + Z_AXIS, z) == Status_OK);
    queue_motion_program("G1X1Y1Z1F100");
    execute_motion_program();
    const unsigned expected[] = {88, 84, 90};
    for(unsigned axis = 0; axis < 3; axis++) {
        CHECK(axis_pulses[axis] == expected[axis]);
        CHECK(sys.position[axis] == 80);
        CHECK(physical_position[axis] == (int32_t)expected[axis]);
        NEAR(gc_state.position[axis], 1);
    }
    return EXIT_SUCCESS;
}
