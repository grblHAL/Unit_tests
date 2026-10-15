#include "support/gcode_comment_host.h"
int main(void)
{
    prepare_gcode_comments();
    state_set(STATE_CHECK_MODE);
    char input[] = "g90(MSG,Change tool)";
    char *message = NULL; status_code_t status = Status_OK;
    CHECK(strcmp(gc_normalize_block(input, &status, &message), "G90") == 0);
    CHECK(status == Status_OK && !message);
    CHECK(!plain_comment_calls && !process_comment_calls && !message_output_calls);
    return EXIT_SUCCESS;
}
