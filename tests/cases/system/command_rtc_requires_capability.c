#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    CHECK(system_command("$RTC=2026-10-09T12:34:56") == Status_InvalidStatement);
    return EXIT_SUCCESS;
}
