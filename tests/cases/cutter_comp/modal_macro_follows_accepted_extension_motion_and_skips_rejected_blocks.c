#include "support/canned_motion_host.h"
#include "ngc_params.h"

static mc_line_ptr delegated_line;
static bool accept_motion;
static unsigned extension_calls, modal_calls;
static int32_t expected_endpoint;
static status_code_t filter_motion(float *target, plan_line_data_t *data)
{
    extension_calls++;
    return accept_motion ? delegated_line(target, data) : Status_GcodeInvalidTarget;
}
static status_code_t observe_modal_call(macro_id_t id, line_number_t line,
                                       parameter_words_t words, uint32_t repeats)
{
    (void)line;
    CHECK(id == 100 && words.x && repeats == 1);
    CHECK(ngc_call_level() == 1);
    NEAR(gc_state.position[X_AXIS], (float)expected_endpoint / 80);
    CHECK(plan_get_current_block() != NULL);
    float argument;
    CHECK(ngc_param_get(24, &argument));
    NEAR(argument, 12);
    CHECK(ngc_param_set(1, 3));
    modal_calls++;
    return Status_OK;
}

int main(void)
{
    prepare_canned_motion();
    delegated_line = grbl.mc_line;
    CHECK(delegated_line != NULL);
    grbl.mc_line = filter_motion;
    grbl.on_macro_execute = observe_modal_call;
    CHECK(ngc_param_set(1, 99));
    CHECK(canned_block("G66P100X12") == Status_OK);
    CHECK(canned_block("G1X1F100") == Status_GcodeInvalidTarget);
    CHECK(canned_block("G0X2") == Status_GcodeInvalidTarget);
    CHECK(extension_calls == 2 && modal_calls == 0);
    CHECK(axis_pulses[X_AXIS] == 0 && plan_get_current_block() == NULL);
    NEAR(gc_state.position[X_AXIS], 0);

    /* Parser errors cancel modal macro registrations; the sender rearms explicitly. */
    CHECK(gc_state.g66_args == NULL);
    CHECK(canned_block("G66P100X12") == Status_OK);
    accept_motion = true;
    expected_endpoint = 80;
    CHECK(canned_block("G1X1F100") == Status_OK);
    CHECK(modal_calls == 1);
    CHECK(protocol_buffer_synchronize());
    CHECK(physical_position[X_AXIS] == 80 && sys.position[X_AXIS] == 80);
    expected_endpoint = 160;
    CHECK(canned_block("G0X2") == Status_OK);
    CHECK(modal_calls == 2 && extension_calls == 4);
    CHECK(protocol_buffer_synchronize());
    CHECK(physical_position[X_AXIS] == 160 && sys.position[X_AXIS] == 160);
    float parent;
    CHECK(ngc_param_get(1, &parent));
    NEAR(parent, 99);
    CHECK(ngc_call_level() == 0);
    CHECK(canned_block("G67") == Status_OK && gc_state.g66_args == NULL);
    execute_canned("G1X3F100");
    CHECK(modal_calls == 2 && extension_calls == 5);
    CHECK(physical_position[X_AXIS] == 240 && sys.position[X_AXIS] == 240);
    CHECK(axis_pulses[X_AXIS] == 240);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(sys.alarm == Alarm_None && !sys.abort);
    return EXIT_SUCCESS;
}
