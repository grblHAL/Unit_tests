#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    state_set(STATE_HOMING);
    CHECK(state_get() == STATE_HOMING);
    CHECK(system_command("$J=G91X1F100") == Status_IdleError);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
