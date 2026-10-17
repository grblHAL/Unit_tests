#include "support/serial_loop_host.h"
int main(void)
{
    run_serial_program("G0X1(note)Y2\b3\n", 1);
    CHECK(sys.position[X_AXIS] == 80 && axis_pulses[X_AXIS] == 80);
    CHECK(sys.position[Y_AXIS] == 240 && axis_pulses[Y_AXIS] == 240);
    CHECK(strcmp(engine_output, "ok" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
