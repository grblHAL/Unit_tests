#include "support/flow_file_host.h"

int main(void)
{
    prepare_flow_file();
    const char *commands[] = {"O10ENDWHILE", "O10ENDREPEAT"};
    for(unsigned i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
        char block[64];
        strcpy(block, commands[i]);
        CHECK(gc_execute_block(block) == Status_FlowControlSyntaxError);
        CHECK(hal.stream.file != NULL);
        char begin[] = "O20IF[1]", end[] = "O20ENDIF";
        CHECK(gc_execute_block(begin) == Status_OK);
        CHECK(gc_execute_block(end) == Status_OK);
    }
    close_flow_file();
    return EXIT_SUCCESS;
}
