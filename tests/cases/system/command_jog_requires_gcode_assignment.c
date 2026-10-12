#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    CHECK(system_command("$J") == Status_InvalidStatement);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
