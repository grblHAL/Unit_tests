#include "support/motion_program_host.h"
#include "ngc_params.h"

int main(void)
{
    prepare_motion_program();
    char seed[] = "#<cut_depth>=99";
    CHECK(gc_execute_block(seed) == Status_OK);
    CHECK(ngc_param_set(100, 88));
    queue_motion_program("G1X1F100");
    plan_block_t *first = plan_get_current_block();
    unsigned available = plan_get_block_buffer_available();
    const struct { const char *text; status_code_t expected; } cases[] = {
        {"#<cut_depth>=[1/0]", Status_ExpressionDivideByZero},
        {"#<cut_depth>=[SIN1]", Status_ExpressionSyntaxError},
        {"#[1/0]=7", Status_ExpressionDivideByZero}
    };
    for(unsigned i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        char block[64]; strcpy(block, cases[i].text);
        CHECK(gc_execute_block(block) == cases[i].expected);
        CHECK(plan_get_current_block() == first && plan_get_block_buffer_available() == available);
        char name[] = "cut_depth";
        float value;
        CHECK(ngc_named_param_get(name, &value)); NEAR(value, 99);
        CHECK(ngc_param_get(100, &value)); NEAR(value, 88);
        CHECK(ngc_call_level() == 0 && !sys.abort && sys.alarm == Alarm_None);
        CHECK(!gc_state.modal.units_imperial && !gc_state.modal.distance_incremental);
        NEAR(gc_state.position[X_AXIS], 1);
        NEAR(gc_state.feed_rate, 100);
        for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(axis_pulses[axis] == 0);
    }
    char retry_name[] = "#<cut_depth>=[1+2]", retry_index[] = "#[50+50]=7";
    CHECK(gc_execute_block(retry_name) == Status_OK);
    CHECK(gc_execute_block(retry_index) == Status_OK);
    char name[] = "cut_depth";
    float value;
    CHECK(ngc_named_param_get(name, &value)); NEAR(value, 3);
    CHECK(ngc_param_get(100, &value)); NEAR(value, 7);
    queue_motion_program("G1X2F100");
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 160 && physical_position[X_AXIS] == 160);
    CHECK(sys.position[X_AXIS] == 160 && plan_get_current_block() == NULL);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
