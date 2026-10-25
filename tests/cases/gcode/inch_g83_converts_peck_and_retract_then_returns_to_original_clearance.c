#include "support/partial_peck_motion_host.h"
int main(void)
{
    prepare_partial_peck_motion();
    execute_canned("G20G0Z0.25");
    CHECK(physical_position[Z_AXIS] == 508);
    axis_pulses[Z_AXIS] = 0;
    execute_canned("G90G98G83X0.5Z-0.125R0.125Q0.1F4");
    NEAR(gc_state.canned.delta, 2.54f);
    NEAR(gc_state.canned.retract_position, 3.175f);
    CHECK(partial_peck_deepest_z == -254);
    CHECK(physical_position[Z_AXIS] == 508 && sys.position[Z_AXIS] == 508);
    CHECK(axis_pulses[Z_AXIS] == 3758);
    CHECK(physical_position[X_AXIS] == 1016 && axis_pulses[X_AXIS] == 1016);
    CHECK(axis_pulses[Y_AXIS] == 0);
    NEAR(gc_state.position[Z_AXIS], 6.35f);
    execute_canned("X0.75"); /* Reuse the converted modal Q/R/depth. */
    CHECK(partial_peck_deepest_z == -254 && physical_position[Z_AXIS] == 508);
    CHECK(physical_position[X_AXIS] == 1524 && axis_pulses[X_AXIS] == 1524);
    CHECK(axis_pulses[Z_AXIS] == 7516 && axis_pulses[Y_AXIS] == 0);
    NEAR(gc_state.canned.delta, 2.54f);
    engine_output[0] = '\0';
    report_gcode_modes(hal.stream.write);
    CHECK(strstr(engine_output, " G20 ") != NULL);
    CHECK(strstr(engine_output, " G98 ") != NULL);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
