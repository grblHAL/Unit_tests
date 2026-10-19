/* Unregistered: coordinate-rotation pivot contract pending Terje; see tests/TODO.md. */
#include "support/rotated_arc_motion_host.h"
int main(void)
{
    prepare_rotated_arc(90);
    char offset[] = "G10L2P2X3Y4";
    CHECK(gc_execute_block(offset) == Status_OK);
    queue_motion_program("G55G0X0Y0");
    queue_motion_program("G3X1Y1J1F100");
    execute_motion_program();
    fprintf(stderr, "translated arc: steps=%ld,%ld physical=%ld,%ld pulses=%u,%u rotation=%g\n", (long)sys.position[0], (long)sys.position[1], (long)physical_position[0], (long)physical_position[1], axis_pulses[0], axis_pulses[1], (double)gc_state.modal.g5x_offset.data.rotation);
    CHECK(sys.position[X_AXIS] == 160 && physical_position[X_AXIS] == 160);
    CHECK(sys.position[Y_AXIS] == 400 && physical_position[Y_AXIS] == 400);
    CHECK(axis_pulses[X_AXIS] == 320 && axis_pulses[Y_AXIS] == 400);
    CHECK(axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
