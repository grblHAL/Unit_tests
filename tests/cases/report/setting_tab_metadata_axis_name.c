#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    CHECK(report_settings_details(SettingsFormat_grblHAL, Setting_AxisStepsPerMM, Group_All) == Status_OK);
    CHECK(strncmp(engine_output, "100\tX-axis travel resolution\tstep/mm\tfloat", strlen("100\tX-axis travel resolution\tstep/mm\tfloat")) == 0);
    return EXIT_SUCCESS;
}
