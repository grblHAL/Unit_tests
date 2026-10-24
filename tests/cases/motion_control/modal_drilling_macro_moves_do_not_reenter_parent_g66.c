#include "support/canned_motion_host.h"
#include "ngc_params.h"

static unsigned macro_calls;
static void run_drilling_command(const char *text)
{
    status_code_t status = canned_block(text);
    if(status != Status_OK) fprintf(stderr, "drilling command %s: status=%u calls=%u scope=%u\n", text, (unsigned)status, macro_calls, (unsigned)ngc_call_level());
    CHECK(status == Status_OK);
    CHECK(protocol_buffer_synchronize());
    CHECK(plan_get_current_block() == NULL);
}
static status_code_t drill(macro_id_t id, line_number_t line, parameter_words_t words, uint32_t repeats)
{
    (void)line;
    CHECK(id == 100 && words.a && repeats == 1 && ngc_call_level() == 1);
    CHECK(++macro_calls <= 5);
    float depth;
    CHECK(ngc_param_get(1, &depth)); NEAR(depth, 1);
    CHECK(canned_block("M73") == Status_OK);
    if(words.x) {
        float x;
        CHECK(ngc_param_get(24, &x));
        char position[32];
        snprintf(position, sizeof(position), "G90G0X%.0f", x);
        run_drilling_command(position);
    }
    run_drilling_command("G91G1Z-1F100");
    const int32_t hole_x[] = {80, 160, 320, 400, 480};
    CHECK(physical_position[X_AXIS] == hole_x[macro_calls - 1]);
    CHECK(physical_position[Z_AXIS] == -80);
    run_drilling_command("G0Z1");
    CHECK(physical_position[Z_AXIS] == 0);
    return Status_OK;
}
int main(void)
{
    prepare_canned_motion();
    grbl.on_macro_execute = drill;
    run_drilling_command("G90G66P100A1");
    CHECK(macro_calls == 0);
    run_drilling_command("G0X1");
    CHECK(macro_calls == 1 && ngc_call_level() == 0);
    CHECK(!gc_state.modal.distance_incremental);
    run_drilling_command("G1X2F100");
    CHECK(macro_calls == 2 && ngc_call_level() == 0);
    CHECK(!gc_state.modal.distance_incremental);
    run_drilling_command("G67");
    run_drilling_command("G0X3");
    CHECK(macro_calls == 2 && gc_state.g66_args == NULL);
    CHECK(axis_pulses[X_AXIS] == 240 && physical_position[X_AXIS] == 240);
    CHECK(axis_pulses[Z_AXIS] == 320 && physical_position[Z_AXIS] == 0);
    CHECK(sys.position[X_AXIS] == 240 && sys.position[Z_AXIS] == 0);
    NEAR(gc_state.position[X_AXIS], 3); NEAR(gc_state.position[Z_AXIS], 0);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        if(axis != X_AXIS && axis != Z_AXIS) CHECK(axis_pulses[axis] == 0);
    run_drilling_command("G66.1P100A1X4");
    CHECK(macro_calls == 3 && ngc_call_level() == 0);
    run_drilling_command("X5");
    CHECK(macro_calls == 4);
    run_drilling_command("X6");
    CHECK(macro_calls == 5 && ngc_call_level() == 0);
    CHECK(!gc_state.modal.distance_incremental);
    run_drilling_command("G67");
    run_drilling_command("G0X7");
    CHECK(macro_calls == 5 && gc_state.g66_args == NULL);
    CHECK(axis_pulses[X_AXIS] == 560 && physical_position[X_AXIS] == 560);
    CHECK(axis_pulses[Z_AXIS] == 800 && physical_position[Z_AXIS] == 0);
    CHECK(sys.position[X_AXIS] == 560 && sys.position[Z_AXIS] == 0);
    NEAR(gc_state.position[X_AXIS], 7); NEAR(gc_state.position[Z_AXIS], 0);
    return EXIT_SUCCESS;
}
