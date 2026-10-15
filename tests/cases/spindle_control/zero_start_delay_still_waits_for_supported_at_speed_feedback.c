#include "support/spindle_ready_host.h"
int main(void)
{
    prepare_spindle_ready(800, 0);
    CHECK(ready_block("M3S6000") == Status_OK);
    CHECK(engine_ticks == 800 && ready_queries == 4);
    CHECK(ready_notifications == 1 && ready_hardware.on);
    CHECK(sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
