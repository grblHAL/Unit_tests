#include "support/system_command_host.h"
#include "ngc_params.h"
int main(void)
{
    prepare_system_command();
    CHECK(ngc_param_set(100, 7));
    CHECK(system_command("$#=100.5") == Status_OK);
    CHECK(strcmp(engine_output, "[PARAM:100.5=N/A]" ASCII_EOL) == 0);
    engine_output[0] = '\0';
    CHECK(system_command("$#=100") == Status_OK);
    CHECK(strcmp(engine_output, "[PARAM:100=7]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
