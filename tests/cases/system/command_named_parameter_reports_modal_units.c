#include "support/system_command_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    char block[] = "G20";
    CHECK(gc_execute_block(block) == Status_OK);
    CHECK(system_command("$#=_imperial") == Status_OK);
    CHECK(strstr(engine_output, "[PARAM:_imperial=1]") != NULL);
    return EXIT_SUCCESS;
}
