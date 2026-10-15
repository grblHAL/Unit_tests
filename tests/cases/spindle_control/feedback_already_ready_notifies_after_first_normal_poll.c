#include "support/spindle_ready_host.h"
int main(void)
{
    prepare_spindle_ready(0, 1000);
    CHECK(ready_block("M3S6000") == Status_OK);
    // Startup feedback uses 200 ms polling, including its first sample.
    CHECK(engine_ticks == 200 && ready_queries == 1);
    CHECK(ready_notifications == 1 && ready_hardware.on);
    CHECK(sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
