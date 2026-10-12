#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    CHECK(report_grbl_setting(Setting_AxisStepsPerMM, NULL) == Status_OK);
    CHECK(strncmp(engine_output, "$100=80.", 8) == 0);
    CHECK(strstr(engine_output, ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
