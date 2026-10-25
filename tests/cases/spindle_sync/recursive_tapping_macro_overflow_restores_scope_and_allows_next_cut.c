#include "support/encoder_thread_motion_host.h"
static unsigned recursive_calls;
static status_code_t recursive_tapping(macro_id_t id, line_number_t line, parameter_words_t args, uint32_t repeats)
{
    (void)line;
    CHECK(id == 331 && args.z && args.k && args.i && repeats == 1);
    unsigned level = ngc_call_level();
    CHECK(level == ++recursive_calls && recursive_calls <= 32);
    CHECK(ngc_param_set(1, 7));
    status_code_t status = sync_parser_block("G33.1Z-1K1I2");
    CHECK(status == Status_FlowControlStackOverflow && ngc_call_level() == level);
    float local;
    CHECK(ngc_param_get(1, &local)); NEAR(local, 7);
    return status;
}
int main(void)
{
    prepare_encoder_thread_motion();
    grbl.on_macro_execute = recursive_tapping;
    CHECK(ngc_param_set(1, 99));
    gc_override_flags_t original = sys.override.control;
    CHECK(sync_parser_block("G33.1Z-1K1I2") == Status_FlowControlStackOverflow);
    CHECK(recursive_calls > 1 && ngc_call_level() == 0);
    float caller;
    CHECK(ngc_param_get(1, &caller)); NEAR(caller, 99);
    CHECK(sys.override.control.value == original.value);
    CHECK(plan_get_current_block() == NULL && sync_encoder_resets == 0);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(axis_pulses[axis] == 0);
    CHECK(sync_parser_block("G33Z1K1") == Status_OK);
    CHECK(axis_pulses[Z_AXIS] == 80 && physical_position[Z_AXIS] == 80 && sys.position[Z_AXIS] == 80);
    CHECK(physical_position[X_AXIS] == 800 && axis_pulses[X_AXIS] == 0 && axis_pulses[Y_AXIS] == 0);
    CHECK(sync_encoder_resets == 1 && plan_get_current_block() == NULL);
    CHECK(!sys.abort && sys.alarm == Alarm_None && ngc_call_level() == 0);
    CHECK(sys.override.control.value == original.value);
    return EXIT_SUCCESS;
}
