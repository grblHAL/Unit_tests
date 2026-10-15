#include "support/serial_loop_host.h"
int main(void)
{
    run_serial_program("G0X1(note)\b! and ?)\n", 1);
    CHECK(sys.position[X_AXIS] == 80 && axis_pulses[X_AXIS] == 80);
    CHECK(strcmp(engine_output, "ok" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
