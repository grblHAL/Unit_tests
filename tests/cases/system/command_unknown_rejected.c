#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    CHECK(system_command("$DOESNOTEXIST") == Status_InvalidStatement);
    CHECK(state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
