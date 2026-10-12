#include "support/serial_loop_host.h"
#include "check.h"

int main(void)
{
    run_serial_program("\n", 1);
    CHECK(sys.position[X_AXIS] == 0);
    CHECK(strcmp(engine_output, "ok" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
