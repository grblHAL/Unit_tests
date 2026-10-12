#include "support/delta_api_host.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    grbl.on_report_options(false);
    CHECK(delta_option_calls == 1 && !delta_option_new);
    CHECK(strcmp(engine_output, "[KINEMATICS:Delta v0.05]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
