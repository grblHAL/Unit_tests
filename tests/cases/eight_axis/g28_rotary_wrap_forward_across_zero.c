#include "support/canned_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_motion();
    settings.steppers.is_rotary.mask = 1u << 3;
    settings.steppers.rotary_wrap.mask = 1u << 3;
    sys.position[3] = physical_position[3] = 710 * 80;
    sync_position();
    coord_system_data_t home = {0};
    home.coord.values[3] = 10;
    settings_write_coord_data(CoordinateSystem_G28, &home);
    execute_canned("G91G28A0");
    CHECK(axis_pulses[3] == 1600);
    CHECK(physical_position[3] == 730 * 80);
    CHECK(sys.position[3] == 10 * 80);
    NEAR(gc_state.position[3], 10);
    for(unsigned axis = 0; axis < N_AXIS; axis++) if(axis != 3) CHECK(axis_pulses[axis] == 0);
    return EXIT_SUCCESS;
}
