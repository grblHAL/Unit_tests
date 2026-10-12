#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    CHECK(system_command("$C") == Status_OK);
    CHECK(state_get() == STATE_CHECK_MODE);
    CHECK(!(sys.rt_exec_state & EXEC_RESET));
    return EXIT_SUCCESS;
}
