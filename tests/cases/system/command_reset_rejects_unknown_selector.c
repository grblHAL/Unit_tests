#include "support/system_command_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    CHECK(system_command("$RST=Q") == Status_InvalidStatement);
    CHECK(!(sys.rt_exec_state & EXEC_RESET));
    return EXIT_SUCCESS;
}
