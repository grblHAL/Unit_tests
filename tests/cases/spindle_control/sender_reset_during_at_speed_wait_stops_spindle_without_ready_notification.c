#include "support/spindle_ready_host.h"
#include "motion_control.h"
static unsigned reset_requests;
static unsigned driver_resets, coolant_stops;
static void reset_driver(void) { driver_resets++; }
static void reset_coolant(coolant_state_t state)
{
    CHECK(state.value == 0);
    coolant_stops++;
}
static void reset_while_starting(sys_state_t state)
{
    (void)state;
    if(engine_ticks >= 100 && reset_requests == 0) {
        reset_requests++;
        mc_reset();
    }
}
int main(void)
{
    prepare_spindle_ready(1000, 2000);
    hal.coolant.set_state = reset_coolant;
    hal.driver_reset = reset_driver;
    grbl.on_execute_realtime = reset_while_starting;
    (void)ready_block("M3S6000");
    CHECK(reset_requests == 1);
    CHECK(driver_resets == 1 && coolant_stops >= 1);
    CHECK(sys.abort);
    CHECK(!ready_hardware.on);
    NEAR(ready_rpm, 0);
    CHECK(ready_notifications == 0);
    CHECK(engine_ticks < ready_after_ms);
    CHECK(sys.alarm != Alarm_Spindle);
    return EXIT_SUCCESS;
}
