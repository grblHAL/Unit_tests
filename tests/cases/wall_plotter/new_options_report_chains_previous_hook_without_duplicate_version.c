#include "support/wall_options_host.h"
int main(void)
{
    prepare_wall_options();
    grbl.on_report_options(true);
    CHECK(wall_previous_options_calls == 1 && wall_previous_newopt);
    CHECK(engine_output[0] == 0);
    return EXIT_SUCCESS;
}
