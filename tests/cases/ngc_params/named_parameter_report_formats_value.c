#include "support/report_host.h"
#include "ngc_params.h"

#include "check.h"

int main(void)
{
    prepare_report();
    char name[] = "report_value";
    CHECK(ngc_named_param_set(name, -2.5f));
    CHECK(report_named_ngc_parameter(name) == Status_OK);
    CHECK(strcmp(engine_output, "[PARAM:report_value=-2.5]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
