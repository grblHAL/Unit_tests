#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    settings.axis[Y_AXIS].steps_per_mm = 160;
    CHECK(report_grbl_setting((setting_id_t)(Setting_AxisStepsPerMM + 1), NULL) == Status_OK);
    CHECK(strncmp(engine_output, "$101=160.", 9) == 0);
    CHECK(strstr(engine_output, ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
