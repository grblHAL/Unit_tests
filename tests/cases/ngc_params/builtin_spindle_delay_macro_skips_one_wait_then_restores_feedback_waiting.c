#include "support/spindle_ready_host.h"
#include "ngc_params.h"
static void record_macro_wait(spindle_ptrs_t *spindle, spindle_state_t state)
{
    CHECK(spindle == spindle_get(0) && state.on);
    if(ready_notifications == 0) CHECK(engine_ticks == 0 && ready_queries == 0);
    else CHECK(engine_ticks == 400 && ready_queries == 2);
    ready_notifications++;
}
int main(void)
{
    prepare_spindle_ready(400, 1000);
    grbl.on_spindle_at_speed = record_macro_wait;
    CHECK(ready_block("G65P6") == Status_OK);
    CHECK(ngc_call_level() == 0);
    CHECK(ready_block("M3S6000") == Status_OK);
    CHECK(ready_hardware.on && !ready_hardware.ccw && ready_notifications == 1);
    NEAR(ready_rpm, 6000);
    CHECK(engine_ticks == 0 && ready_queries == 0);
    CHECK(!sys.override.control.spindle_wait_disable);
    CHECK(ready_block("M4S6000") == Status_OK);
    CHECK(ready_hardware.on && ready_hardware.ccw && ready_notifications == 2);
    CHECK(engine_ticks == 400 && ready_queries == 2);
    CHECK(!sys.override.control.spindle_wait_disable && ngc_call_level() == 0);
    CHECK(sys.alarm == Alarm_None && !sys.abort);
    return EXIT_SUCCESS;
}
