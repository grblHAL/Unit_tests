#include "support/system_command_host.h"
#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    CHECK(system_command("$SED") == Status_BadNumberFormat);
    CHECK(system_command("$SED=ABC") == Status_BadNumberFormat);
    CHECK(engine_output[0] == '\0');
    return EXIT_SUCCESS;
}
