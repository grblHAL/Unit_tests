#include "support/serial_loop_host.h"
#include "check.h"

int main(void)
{
    run_serial_program("G0X1\nG1X2F100\n", 2);
    CHECK(sys.position[X_AXIS] == 160);
    CHECK(axis_pulses[X_AXIS] == 160);
    CHECK(strcmp(engine_output, "ok" ASCII_EOL "ok" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
