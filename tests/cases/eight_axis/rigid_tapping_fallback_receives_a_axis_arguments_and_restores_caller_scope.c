#include "support/macro_parser_host.h"
#include "state_machine.h"
static spindle_data_t feedback;
static spindle_state_t spindle_state;
static unsigned tapping_calls;
static void spindle_output(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{ (void)spindle; spindle_state = state; feedback.rpm = state.on ? rpm : 0; }
static spindle_state_t spindle_input(spindle_ptrs_t *spindle)
{ (void)spindle; return spindle_state; }
static spindle_data_t *spindle_feedback(spindle_data_request_t request)
{ (void)request; return &feedback; }
static control_signals_t no_controls(void) { return (control_signals_t){0}; }
static bool connected(void) { return true; }
static status_code_t observe_tapping(macro_id_t id, line_number_t line, parameter_words_t args, uint32_t repeats)
{
    CHECK(id == 331 && line == 27 && repeats == 1 && ngc_call_level() == 1);
    CHECK(args.a && args.i && args.k && args.z && !args.x && !args.y);
    float value;
    CHECK(ngc_param_get(1, &value)); NEAR(value, 12.5f);
    CHECK(ngc_param_get(4, &value)); NEAR(value, 2);
    CHECK(ngc_param_get(6, &value)); NEAR(value, .75f);
    CHECK(ngc_param_get(26, &value)); NEAR(value, -3);
    tapping_calls++;
    return Status_OK;
}
int main(void)
{
    engine_prepare();
    sys.cold_start = true;
    hal.control.get_state = no_controls;
    hal.stream.is_connected = connected;
    spindle_ptrs_t driver = {.type = SpindleType_VFD, .ref_id = 10,
        .rpm_min = 1, .rpm_max = 1000,
        .cap = {.enable = true, .variable = true, .direction = true, .rpm_range_locked = true},
        .set_state = spindle_output, .get_state = spindle_input, .get_data = spindle_feedback};
    CHECK(spindle_register(&driver, "Encoder spindle") == 0 && spindle_select(0));
    coord_system_data_t coordinates = {0};
    for(unsigned i = 0; i < N_CoordinateSystems; i++) settings_write_coord_data((coord_system_id_t)i, &coordinates);
    gc_init(false);
    CHECK(plan_reset());
    limits_init();
    report_init_fns();
    sys.cold_start = false;
    state_set(STATE_IDLE);
    grbl.on_macro_execute = observe_tapping;
    CHECK(ngc_param_set(1, 99) && ngc_param_set(26, 88));
    CHECK(macro_block("M3S100") == Status_OK);
    CHECK(macro_block("N27G33.1A12.5Z-3K0.75I2") == Status_OK);
    CHECK(tapping_calls == 1 && ngc_call_level() == 0);
    float value;
    CHECK(ngc_param_get(1, &value)); NEAR(value, 99);
    CHECK(ngc_param_get(26, &value)); NEAR(value, 88);
    CHECK(plan_get_current_block() == NULL && !sys.abort && sys.alarm == Alarm_None);
    CHECK(!sys.override.control.feed_rates_disable && !sys.override.control.spindle_rpm_disable);
    return EXIT_SUCCESS;
}
