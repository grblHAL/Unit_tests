#include "support/spindle_ready_host.h"
static void delay_notified(spindle_ptrs_t *spindle, spindle_state_t state)
{
    CHECK(spindle == spindle_get(0) && state.on);
    CHECK(engine_ticks == 400);
    ready_notifications++;
}
int main(void)
{
    prepare_spindle_ready_capabilities(1000, 400,
        (spindle_cap_t){.direction = true, .variable = true, .rpm_range_locked = true});
    grbl.on_spindle_at_speed = delay_notified;
    CHECK(ready_block("M3S6000") == Status_OK);
    CHECK(ready_hardware.on && ready_notifications == 1);
    CHECK(engine_ticks == 400 && ready_queries == 0);
    CHECK(sys.alarm == Alarm_None);
    NEAR(ready_rpm, 6000);
    return EXIT_SUCCESS;
}
