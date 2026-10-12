#include "support/system_command_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    CHECK(system_command("$#=_missing") == Status_OK);
    CHECK(strstr(engine_output, "[PARAM:_missing=N/A]") != NULL);
    return EXIT_SUCCESS;
}
