#include "support/system_command_host.h"
#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program();
    queue_motion_program("G1X10F100");
    state_set(STATE_CYCLE);
    CHECK(state_get() == STATE_CYCLE);
    CHECK(system_command("$$") == Status_IdleError);
    CHECK(system_command("$+") == Status_IdleError);
    CHECK(engine_output[0] == '\0');
    return EXIT_SUCCESS;
}
