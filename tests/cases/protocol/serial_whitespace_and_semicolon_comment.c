#include "support/serial_loop_host.h"
#include "check.h"

int main(void)
{
    run_serial_program(" \t G0 X1 ; X99\n", 1);
    CHECK(sys.position[X_AXIS] == 80);
    CHECK(axis_pulses[X_AXIS] == 80);
    CHECK(strcmp(engine_output, "ok" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
