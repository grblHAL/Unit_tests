#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    sys.homing.mask = 0;
    settings.homing.flags.single_axis_commands = false;
    settings.homing.flags.manual = false;
    status_report_tracking_t tracking = {.flags={.homed=true}};
    report_realtime_status(hal.stream.write, &tracking);
    CHECK(strstr(engine_output, "|H:") == NULL);
    return EXIT_SUCCESS;
}
