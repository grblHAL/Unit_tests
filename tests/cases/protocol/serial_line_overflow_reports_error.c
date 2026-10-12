#include "support/serial_loop_host.h"
#include "check.h"

int main(void)
{
    char program[LINE_BUFFER_SIZE + 50];
    memset(program, '0', sizeof(program));
    program[0] = 'G';
    program[sizeof(program) - 2] = '\n';
    program[sizeof(program) - 1] = 0;
    run_serial_program(program, 1);
    CHECK(sys.position[X_AXIS] == 0);
    CHECK(axis_pulses[X_AXIS] == 0);
    CHECK(strcmp(engine_output, "error:11" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
