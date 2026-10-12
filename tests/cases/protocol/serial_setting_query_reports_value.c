#include "support/serial_loop_host.h"
#include "check.h"

int main(void)
{
    run_serial_program("$12\n", 1);
    CHECK(strstr(engine_output, "$12=0.020" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "ok" ASCII_EOL) != NULL);
    CHECK(axis_pulses[X_AXIS] == 0);
    return EXIT_SUCCESS;
}
