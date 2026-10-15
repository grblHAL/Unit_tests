#include "support/gcode_comment_host.h"
int main(void)
{
    prepare_gcode_comments();
    char input[] = " g90 (MSG,   Change tool) g21";
    char *message = NULL; status_code_t status = Status_OK;
    char *block = gc_normalize_block(input, &status, &message);
    CHECK(status == Status_OK && strcmp(block, "G90G21") == 0);
    CHECK(message && strcmp(message, "Change tool") == 0);
    CHECK(plain_comment_calls == 0);
    free(message);
    char program[] = "(MSG,   Change tool)";
    CHECK(gc_execute_block(program) == Status_OK);
    CHECK(message_output_calls == 1 && strcmp(captured_message, "Change tool") == 0);
    CHECK(strstr(engine_output, "[MSG:Change tool]") != NULL);
    return EXIT_SUCCESS;
}
