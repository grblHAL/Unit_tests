#include "support/canned_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_motion();
    settings.steppers.is_rotary.mask = 1u << 3;
    settings.steppers.rotary_wrap.mask = 1u << 3;
    sys.position[3] = physical_position[3] = 710 * 80;
    sync_position();
    state_set(STATE_CHECK_MODE);
    coord_system_data_t home = {0};
    home.coord.values[3] = 10;
    settings_write_coord_data(CoordinateSystem_G28, &home);
    CHECK(canned_block("G91G28A0") == Status_OK);
    CHECK(axis_pulses[3] == 0);
    CHECK(physical_position[3] == 710 * 80);
    fprintf(stderr, "G28 check mode: machine A steps=%ld; expected %ld with no motion\n", (long)sys.position[3], (long)(710 * 80));
    CHECK(sys.position[3] == 710 * 80);
    return EXIT_SUCCESS;
}
