#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    CHECK(system_command("$SLP") == Status_InvalidStatement);
    CHECK(!(sys.rt_exec_state & EXEC_SLEEP));
    return EXIT_SUCCESS;
}
