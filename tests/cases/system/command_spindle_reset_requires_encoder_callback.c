#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    gc_spindle_get(-1)->hal->reset_data = NULL;
    CHECK(system_command("$SR") == Status_InvalidStatement);
    return EXIT_SUCCESS;
}
