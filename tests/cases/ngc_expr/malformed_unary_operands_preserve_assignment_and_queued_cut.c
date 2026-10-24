#include "support/queued_motion_rejection_host.h"
#include "ngc_params.h"

int main(void)
{
    prepare_motion_program();
    CHECK(ngc_param_set(100, 99));
    queue_motion_program("G1X1F100");
    plan_block_t *first = plan_get_current_block();
    unsigned available = plan_get_block_buffer_available();
    const struct { const char *text; status_code_t status; } cases[] = {
        {"#100=[ATAN[1]/[1/0]]", Status_ExpressionDivideByZero},
        {"#100=[PRM[1.5]]", Status_GcodeCommandValueNotInteger},
        {"#100=[PRM[15,0.5]]", Status_GcodeCommandValueNotInteger},
        {"#100=[EXISTS[2]]", Status_ExpressionSyntaxError},
        {"#100=[EXISTS[#<MISSING]]", Status_ExpressionSyntaxError},
        {"#100=[EXISTS[#<MISSING", Status_ExpressionSyntaxError},
        {"#100=[#<MISSING", Status_FlowControlSyntaxError}
    };
    for(unsigned i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        char command[96];
        strcpy(command, cases[i].text);
        status_code_t actual = gc_execute_block(command);
        if(actual != cases[i].status)
            fprintf(stderr, "%s: status=%u expected=%u\n", cases[i].text, (unsigned)actual, (unsigned)cases[i].status);
        CHECK(actual == cases[i].status);
        CHECK(plan_get_current_block() == first && plan_get_block_buffer_available() == available);
        float value;
        CHECK(ngc_param_get(100, &value));
        NEAR(value, 99);
        NEAR(gc_state.position[X_AXIS], 1);
        CHECK(!sys.abort && sys.alarm == Alarm_None);
    }
    char retry[] = "#100=[ATAN[1]/[1]]";
    CHECK(gc_execute_block(retry) == Status_OK);
    float value;
    CHECK(ngc_param_get(100, &value));
    NEAR(value, 45);
    execute_motion_program();
    CHECK(physical_position[X_AXIS] == 80 && axis_pulses[X_AXIS] == 80);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
