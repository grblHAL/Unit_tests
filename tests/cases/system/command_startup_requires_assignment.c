#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    CHECK(system_command("$N0") == Status_InvalidStatement);
    return EXIT_SUCCESS;
}
