#include "support/multi_spindle_host.h"
#include "report.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle();
    CHECK(report_spindles(false) == Status_OK);
    CHECK(strcmp(engine_output, "0 - primary, enabled as spindle 0" ASCII_EOL
                               "1 - secondary" ASCII_EOL
                               "2 - auxiliary" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
