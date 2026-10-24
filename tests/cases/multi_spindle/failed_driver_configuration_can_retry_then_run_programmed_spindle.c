#include "support/engine_host.h"
#include "spindle_control.h"
#include "state_machine.h"
#include "protocol.h"
#include "report.h"
#include "check.h"

static unsigned configurations, outputs;
static spindle_state_t actual;
static float actual_rpm;
static bool configure_driver(spindle_ptrs_t *spindle)
{
    CHECK(spindle->id == 0);
    return ++configurations > 1;
}
static void set_driver(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    CHECK(spindle->id == 0 || spindle->id == 1);
    actual = state; actual_rpm = rpm; outputs++;
}
static spindle_state_t get_driver(spindle_ptrs_t *spindle)
{ CHECK(spindle->id == 0 || spindle->id == 1); return actual; }
static control_signals_t read_controls(void) { return (control_signals_t){0}; }
int main(void)
{
    engine_prepare();
    sys.cold_start = true;
    static const spindle_ptrs_t driver = {.type = SpindleType_Basic,
        .ref_id = 10, .rpm_min = 100, .rpm_max = 12000,
        .cap = {.direction = true, .rpm_range_locked = true},
        .config = configure_driver, .set_state = set_driver, .get_state = get_driver};
    CHECK(spindle_register(&driver, "retry spindle") == 0);
    static const spindle_ptrs_t alternate = {.type = SpindleType_Basic,
        .ref_id = 20, .rpm_min = 100, .rpm_max = 12000,
        .cap = {.direction = true, .rpm_range_locked = true},
        .set_state = set_driver, .get_state = get_driver};
    CHECK(spindle_register(&alternate, "alternate spindle") == 1);
    CHECK(!spindle_select(0));
    CHECK(configurations == 1 && outputs == 0);
    CHECK(spindle_get_default() == -2 && !spindle_is_enabled(0));
    CHECK(spindle_select(0));
    CHECK(configurations == 2 && spindle_get_default() == 0 && spindle_is_enabled(0));
    CHECK(spindle_select(0) && configurations == 2);
    coord_system_data_t coordinates = {0};
    for(unsigned i = 0; i < N_CoordinateSystems; i++)
        settings_write_coord_data((coord_system_id_t)i, &coordinates);
    gc_init(false);
    CHECK(plan_reset());
    hal.control.get_state = read_controls;
    grbl.on_execute_realtime = protocol_execute_noop;
    report_init_fns();
    state_set(STATE_IDLE);
    char start[] = "M3S1200", stop[] = "M5";
    CHECK(gc_execute_block(start) == Status_OK);
    CHECK(actual.on && !actual.ccw); NEAR(actual_rpm, 1200);
    unsigned running_outputs = outputs;
    CHECK(running_outputs > 0);
    CHECK(gc_execute_block(stop) == Status_OK);
    CHECK(!actual.on && outputs > running_outputs && configurations == 2);
    CHECK(spindle_select(1) && spindle_get_default() == 1);
    CHECK(spindle_select(0) && spindle_get_default() == 0);
    CHECK(configurations == 2 && !actual.on);
    return EXIT_SUCCESS;
}
