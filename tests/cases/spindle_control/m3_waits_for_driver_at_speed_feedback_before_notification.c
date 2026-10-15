#include "support/spindle_ready_host.h"
int main(void)
{
    prepare_spindle_ready(600, 1000);
    CHECK(ready_block("M3S6000") == Status_OK);
    CHECK(engine_ticks == 600 && ready_queries == 3);
    CHECK(ready_notifications == 1 && ready_hardware.on && !ready_hardware.ccw);
    NEAR(ready_rpm, 6000); CHECK(sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
