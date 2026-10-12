#include "support/serial_loop_host.h"
#include "check.h"

int main(void)
{
    run_serial_program("G999\n", 1);
    CHECK(sys.position[X_AXIS] == 0);
    CHECK(axis_pulses[X_AXIS] == 0);
    CHECK(strcmp(engine_output, "error:20" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
