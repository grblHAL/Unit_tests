#include "support/delta_host.h"
#include "report.h"
#include <string.h>

int main(void)
{
    prepare_delta();
    report_init_fns();
    CHECK(report_settings_details(SettingsFormat_MachineReadable, Setting_AxisMaxTravel, Group_All) == Status_OK);
    CHECK(strstr(engine_output, "[SETTING:130|") != NULL);
    CHECK(strstr(engine_output, "X-axis maximum travel|mm|") != NULL);
    engine_output[0] = '\0';
    CHECK(report_setting_description(SettingsFormat_MachineReadable, Setting_AxisMaxTravel) == Status_OK);
    CHECK(strstr(engine_output, "[SETTINGDESCR:130|Maximum axis travel distance from homing switch.") != NULL);
    engine_output[0] = '\0';
    CHECK(report_settings_details(SettingsFormat_MachineReadable, Setting_AxisStepsPerMM, Group_All) == Status_OK);
    CHECK(strstr(engine_output, "X-axis travel resolution|step/rad|") != NULL);
    engine_output[0] = '\0';
    CHECK(report_setting_description(SettingsFormat_MachineReadable, Setting_AxisStepsPerMM) == Status_OK);
    CHECK(strstr(engine_output, "Travel resolution in steps per radian (57.296 degrees).") != NULL);
    CHECK(isfinite(sys.work_envelope.min.z) && isfinite(sys.work_envelope.max.z));
    CHECK(sys.work_envelope.min.z < sys.work_envelope.max.z);
    return EXIT_SUCCESS;
}
