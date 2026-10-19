#include "support/flow_host.h"
#include "ngc_params.h"

int main(void)
{
    prepare_flow();
    const char *commands[] = {"O10ELSEIF[1]", "O10ELSE", "O10ENDIF"};
    for(unsigned i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
        char block[64];
        strcpy(block, commands[i]);
        CHECK(gc_execute_block(block) == Status_FlowControlSyntaxError);
        char begin[] = "O20IF[1]", assignment[] = "#100=23", end[] = "O20ENDIF";
        CHECK(gc_execute_block(begin) == Status_OK);
        CHECK(gc_execute_block(assignment) == Status_OK);
        CHECK(gc_execute_block(end) == Status_OK);
        float value;
        CHECK(ngc_param_get(100, &value));
        NEAR(value, 23);
    }
    return EXIT_SUCCESS;
}
