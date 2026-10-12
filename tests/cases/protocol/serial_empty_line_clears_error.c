#include "support/serial_loop_host.h"
#include "check.h"

int main(void)
{
    run_serial_program("G999\n\nG0X1\n", 3);
    CHECK(sys.position[X_AXIS] == 80);
    CHECK(strcmp(engine_output, "error:20" ASCII_EOL "ok" ASCII_EOL "ok" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
