#include "support/spindle_ready_host.h"
int main(void)
{
    prepare_spindle_ready(400, 400);
    CHECK(ready_block("M3S6000") == Status_OK);
    CHECK(engine_ticks == 400 && ready_queries == 2);
    CHECK(ready_notifications == 1 && ready_hardware.on);
    CHECK(sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
