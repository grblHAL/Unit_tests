#include "support/serial_loop_host.h"
#include "check.h"

int main(void)
{
    run_serial_program("G0X12\1773\n", 1);
    fprintf(stderr, "Final X steps: %ld\n", (long)sys.position[X_AXIS]);
    CHECK(sys.position[X_AXIS] == 1040);
    CHECK(strcmp(engine_output, "ok" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
