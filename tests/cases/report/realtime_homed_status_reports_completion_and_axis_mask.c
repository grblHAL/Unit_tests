#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    sys.homing.mask = X_AXIS_BIT | Y_AXIS_BIT;
    settings.homing.flags.single_axis_commands = true;
    sys.homed.mask = X_AXIS_BIT;
    status_report_tracking_t tracking = {.flags={.homed=true}};
    report_realtime_status(hal.stream.write, &tracking);
    CHECK(strstr(engine_output, "|H:0,1") != NULL);
    engine_output[0] = '\0';
    sys.homed.mask = X_AXIS_BIT | Y_AXIS_BIT;
    tracking.flags.homed = true;
    report_realtime_status(hal.stream.write, &tracking);
    CHECK(strstr(engine_output, "|H:1,3") != NULL);
    return EXIT_SUCCESS;
}
