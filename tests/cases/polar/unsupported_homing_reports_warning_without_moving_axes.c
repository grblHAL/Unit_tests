#include "support/polar_segment_host.h"

int main(void)
{
    prepare_polar_segments();
    sys.position[X_AXIS] = 800; sys.position[Y_AXIS] = 7200; sys.position[Z_AXIS] = 240;
    CHECK(!grbl.home_machine((axes_signals_t){.mask = AXES_BITMASK}, (axes_signals_t){0}));
    CHECK(sys.position[X_AXIS] == 800 && sys.position[Y_AXIS] == 7200 && sys.position[Z_AXIS] == 240);
    CHECK(strstr(engine_output, "Homing is not implemented!") != NULL);
    return EXIT_SUCCESS;
}
