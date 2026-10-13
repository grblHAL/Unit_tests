#include "support/ganging_host.h"

int main(void)
{
    prepare_ganging();
    grbl.on_report_options(true);
    CHECK(ganging_options_calls == 1 && ganging_new_options == true);
    CHECK(engine_output[0] == 0);
    return EXIT_SUCCESS;
}
