#include "support/spindle_ready_host.h"
static void torch_notified(spindle_ptrs_t *spindle, spindle_state_t state)
{
    CHECK(spindle == spindle_get(0));
    CHECK(state.on == ready_hardware.on);
    ready_notifications++;
}
int main(void)
{
    prepare_spindle_ready_capabilities(1000, 2000,
        (spindle_cap_t){.direction = true, .variable = true, .rpm_range_locked = true, .at_speed = true, .torch = true});
    grbl.on_spindle_at_speed = torch_notified;
    settings.spindle.off_delay = 2000;
    CHECK(ready_block("M3S6000") == Status_OK);
    CHECK(ready_hardware.on && ready_notifications == 1);
    CHECK(engine_ticks == 0 && ready_queries == 0);
    NEAR(ready_rpm, 6000);
    CHECK(ready_block("M5") == Status_OK);
    CHECK(!ready_hardware.on && ready_notifications == 2);
    CHECK(engine_ticks == 0 && sys.alarm == Alarm_None);
    NEAR(ready_rpm, 0);
    return EXIT_SUCCESS;
}
