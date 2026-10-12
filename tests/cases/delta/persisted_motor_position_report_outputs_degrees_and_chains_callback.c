#include "support/delta_api_host.h"
#include "report.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    const setting_detail_t *flags = setting_get_details(Setting_Kinematics7, NULL);
    /* Bit 2 is supported in persisted delta flags, although absent from the settings UI. */
    *(uint8_t *)flags->value = 4;
    delta_details()->save();
    *(uint8_t *)flags->value = 0;
    delta_details()->load();
    sys.position[0] = 80; sys.position[1] = 160; sys.position[2] = -80;
    grbl.on_realtime_report(hal.stream.write, (report_tracking_flags_t){0});
    CHECK(strcmp(engine_output, "|KPos:57.30,114.59,-57.30|Fixture:1") == 0);
    CHECK(delta_realtime_calls == 1);
    return EXIT_SUCCESS;
}
