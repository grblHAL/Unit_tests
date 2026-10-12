#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    char command[sizeof(stored_line_t) + 4];
    memcpy(command, "$I=", 3);
    memset(command + 3, 'A', sizeof(stored_line_t) - 1);
    command[sizeof(stored_line_t) + 2] = 0;
    CHECK(system_command(command) == Status_InvalidStatement);
    return EXIT_SUCCESS;
}
