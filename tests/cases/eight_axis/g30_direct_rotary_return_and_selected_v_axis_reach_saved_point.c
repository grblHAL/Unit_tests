#include "support/canned_motion_host.h"

int main(void)
{
    prepare_canned_motion();
    CHECK(N_AXIS == 8);
    settings.steppers.is_rotary.mask = 1u << 3;
    settings.steppers.rotary_wrap.mask = 1u << 3;
    sys.position[3] = physical_position[3] = 270 * 80;
    sync_position();
    coord_system_data_t saved = {0};
    saved.coord.values[0] = 5;
    saved.coord.values[1] = 6;
    saved.coord.values[3] = 10;
    saved.coord.values[7] = 2;
    settings_write_coord_data(CoordinateSystem_G30, &saved);
    /* The rotary shortcut applies to G28; G30 returns to its saved coordinates. */
    execute_canned("G91G30A0V0");
    CHECK(axis_pulses[3] == 20800 && physical_position[3] == 10 * 80);
    CHECK(sys.position[3] == 10 * 80);
    CHECK(axis_pulses[7] == 160 && physical_position[7] == 160 && sys.position[7] == 160);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        if(axis != 3 && axis != 7) CHECK(axis_pulses[axis] == 0);
    return EXIT_SUCCESS;
}
