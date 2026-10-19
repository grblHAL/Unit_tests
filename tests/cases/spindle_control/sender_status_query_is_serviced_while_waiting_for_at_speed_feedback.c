#include "support/spindle_ready_host.h"
static unsigned status_requests;
static bool status_before_ready;
static coolant_state_t query_coolant(void) { return (coolant_state_t){0}; }
static void query_while_starting(sys_state_t state)
{
    (void)state;
    if(engine_ticks >= 100 && status_requests == 0) {
        status_requests++;
        CHECK(protocol_enqueue_realtime_command(CMD_STATUS_REPORT));
    }
    if(strstr(engine_output, "<Idle|") != NULL && engine_ticks < ready_after_ms)
        status_before_ready = true;
}
int main(void)
{
    prepare_spindle_ready(600, 1000);
    hal.coolant.get_state = query_coolant;
    engine_output[0] = '\0';
    grbl.on_execute_realtime = query_while_starting;
    CHECK(ready_block("M3S6000") == Status_OK);
    CHECK(status_requests == 1 && status_before_ready);
    CHECK(ready_notifications == 1 && ready_hardware.on);
    CHECK(engine_ticks == 600);
    CHECK(sys.alarm == Alarm_None && !sys.abort);
    return EXIT_SUCCESS;
}
