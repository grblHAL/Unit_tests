#include "support/report_host.h"
#include "ngc_params.h"

#include "check.h"

int main(void)
{
    prepare_report();
    CHECK(ngc_param_set(100, 12.5f));
    CHECK(report_ngc_parameter(100) == Status_OK);
    CHECK(strcmp(engine_output, "[PARAM:100=12.5]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
