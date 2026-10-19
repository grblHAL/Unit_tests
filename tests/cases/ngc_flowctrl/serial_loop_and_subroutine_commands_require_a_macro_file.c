#include "support/flow_host.h"
#include "ngc_params.h"

int main(void)
{
    prepare_flow();
    const char *commands[] = {"O10DO", "O10WHILE[1]", "O10ENDWHILE",
        "O10REPEAT[2]", "O10ENDREPEAT", "O10BREAK", "O10CONTINUE",
        "O10SUB", "O10ENDSUB", "O10CALL", "O10RETURN"};
    for(unsigned i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
        char block[64];
        strcpy(block, commands[i]);
        CHECK(gc_execute_block(block) == Status_FlowControlNotExecutingMacro);
        CHECK(hal.stream.file == NULL);
        char recovery[] = "#100=17";
        CHECK(gc_execute_block(recovery) == Status_OK);
        float value;
        CHECK(ngc_param_get(100, &value));
        NEAR(value, 17);
    }
    return EXIT_SUCCESS;
}
