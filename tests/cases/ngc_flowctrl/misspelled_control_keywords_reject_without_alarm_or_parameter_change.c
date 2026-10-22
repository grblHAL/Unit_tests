#include "support/flow_host.h"
#include "ngc_params.h"
int main(void)
{
    prepare_flow();
    CHECK(ngc_param_set(100, 42));
    /* Common incomplete/misspelled macro words must not execute a different action. */
    const char *invalid[] = {"O10ALAM[2]", "O10BREK", "O10CONTINE",
        "O10D0", "O10ENIF", "O10I[1]", "O10REPET[2]",
        "O10SBU", "O10WHLE[1]", "O10XYZ", "O10Z[1]"};
    for(unsigned i = 0; i < sizeof(invalid) / sizeof(invalid[0]); i++) {
        char block[64];
        CHECK(strlen(invalid[i]) < sizeof(block));
        strcpy(block, invalid[i]);
        status_code_t status = gc_execute_block(block);
        CHECK(status == Status_FlowControlSyntaxError);
        float value;
        CHECK(ngc_param_get(100, &value));
        NEAR(value, 42);
        CHECK(sys.alarm == Alarm_None && !sys.abort);
        CHECK(plan_get_current_block() == NULL);
    }
    char bare_label[] = "O10";
    CHECK(gc_execute_block(bare_label) == Status_GcodeUnusedWords);
    char begin[] = "O20IF[1]", assign[] = "#100=43", end[] = "O20ENDIF";
    CHECK(gc_execute_block(begin) == Status_OK);
    CHECK(gc_execute_block(assign) == Status_OK);
    CHECK(gc_execute_block(end) == Status_OK);
    float value;
    CHECK(ngc_param_get(100, &value));
    NEAR(value, 43);
    return EXIT_SUCCESS;
}
