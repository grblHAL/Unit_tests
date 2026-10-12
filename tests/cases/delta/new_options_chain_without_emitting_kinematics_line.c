#include "support/delta_api_host.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    grbl.on_report_options(true);
    CHECK(delta_option_calls == 1 && delta_option_new);
    CHECK(engine_output[0] == 0);
    return EXIT_SUCCESS;
}
