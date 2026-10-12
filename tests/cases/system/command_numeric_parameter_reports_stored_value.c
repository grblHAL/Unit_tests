#include "support/system_command_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    CHECK(ngc_param_set(100, 12.5f));
    CHECK(system_command("$#=100") == Status_OK);
    CHECK(strstr(engine_output, "[PARAM:100=12.5]") != NULL);
    return EXIT_SUCCESS;
}
