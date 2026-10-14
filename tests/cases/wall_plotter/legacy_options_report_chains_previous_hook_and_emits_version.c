#include "support/wall_options_host.h"
int main(void)
{
    prepare_wall_options();
    grbl.on_report_options(false);
    CHECK(wall_previous_options_calls == 1 && !wall_previous_newopt);
    CHECK(strcmp(engine_output,"[KINEMATICS:WallPlotter v2.01]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
