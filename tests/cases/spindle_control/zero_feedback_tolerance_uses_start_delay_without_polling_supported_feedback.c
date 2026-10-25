#include "support/spindle_ready_host.h"
static void tolerance_disabled_notification(spindle_ptrs_t *spindle, spindle_state_t state)
{
    CHECK(spindle == spindle_get(0) && state.on == ready_hardware.on);
    CHECK(engine_ticks == 500 && ready_queries == 0);
    ready_notifications++;
}
int main(void)
{
    ready_tolerance = 0;
    prepare_spindle_ready(2000, 500);
    CHECK(spindle_get(0)->cap.at_speed);
    NEAR(spindle_get(0)->at_speed_tolerance, 0);
    grbl.on_spindle_at_speed = tolerance_disabled_notification;
    CHECK(ready_block("M3S6000") == Status_OK);
    CHECK(ready_hardware.on && ready_notifications == 1);
    NEAR(ready_rpm, 6000);
    CHECK(engine_ticks == 500 && ready_queries == 0);
    CHECK(ready_block("M5") == Status_OK);
    CHECK(!ready_hardware.on && ready_notifications == 2);
    CHECK(engine_ticks == 500 && ready_queries == 0);
    CHECK(sys.alarm == Alarm_None && !sys.abort);
    return EXIT_SUCCESS;
}
