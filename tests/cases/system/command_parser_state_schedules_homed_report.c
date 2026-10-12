#include "support/system_command_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    hal.stream.report.flags.value = 0;
    CHECK(system_command("$G") == Status_OK);
    CHECK(strstr(engine_output, "[GC:") != NULL);
    CHECK(hal.stream.report.flags.value & Report_Homed);
    return EXIT_SUCCESS;
}
