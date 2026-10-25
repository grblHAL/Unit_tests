#include "support/partial_peck_motion_host.h"
int main(void)
{
    prepare_partial_peck_motion();
    char retract[] = "0.127"; /* The setting stays in mm while the program uses inches. */
    CHECK(settings_store_setting(Setting_G73Retract, retract) == Status_OK);
    execute_canned("G20G91G99G73X0.125Z-0.125R0.025Q0.05L3F4");
    NEAR(gc_state.canned.delta, 1.27f);
    NEAR(gc_state.canned.retract_position, .635f);
    CHECK(partial_peck_deepest_z == -203);
    CHECK(physical_position[Z_AXIS] == 51 && sys.position[Z_AXIS] == 51);
    CHECK(axis_pulses[Z_AXIS] == 1695);
    CHECK(physical_position[X_AXIS] == 762 && axis_pulses[X_AXIS] == 762);
    CHECK(axis_pulses[Y_AXIS] == 0);
    NEAR(gc_state.position[Z_AXIS], .635f);
    execute_canned("X0.125L2"); /* Continue the same cycle without Q/R/Z. */
    CHECK(partial_peck_deepest_z == -203 && physical_position[Z_AXIS] == 51);
    CHECK(physical_position[X_AXIS] == 1270 && axis_pulses[X_AXIS] == 1270);
    CHECK(axis_pulses[Z_AXIS] == 2791 && axis_pulses[Y_AXIS] == 0);
    NEAR(gc_state.canned.delta, 1.27f);
    engine_output[0] = '\0';
    report_gcode_modes(hal.stream.write);
    CHECK(strstr(engine_output, " G20 ") != NULL);
    CHECK(strstr(engine_output, " G99 ") != NULL);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
