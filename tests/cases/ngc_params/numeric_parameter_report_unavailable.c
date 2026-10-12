#include "support/report_host.h"
#include "ngc_params.h"

#include "check.h"

int main(void)
{
    prepare_report();
    CHECK(report_ngc_parameter(0) == Status_OK);
    CHECK(strcmp(engine_output, "[PARAM:0=N/A]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
