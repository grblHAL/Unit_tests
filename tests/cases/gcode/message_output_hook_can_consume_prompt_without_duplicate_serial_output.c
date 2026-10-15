#include "support/gcode_comment_host.h"
int main(void)
{
    prepare_gcode_comments();
    consume_output_message = true;
    char input[] = "(MSG,Change tool)";
    CHECK(gc_execute_block(input) == Status_OK);
    CHECK(message_output_calls == 1 && strcmp(captured_message, "Change tool") == 0);
    CHECK(engine_output[0] == '\0');
    return EXIT_SUCCESS;
}
