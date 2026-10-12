#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    CHECK(system_command("$ c ") == Status_OK);
    CHECK(state_get() == STATE_CHECK_MODE);
    return EXIT_SUCCESS;
}
