#include "support/ganging_host.h"

int main(void)
{
    prepare_ganging();
    grbl.on_report_options(false);
    CHECK(ganging_options_calls == 1 && ganging_new_options == false);
    CHECK(strcmp(engine_output, "[KINEMATICS:Asymmetric ganging v0.02]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
