#include "support/gcode_comment_host.h"
int main(void)
{
    prepare_gcode_comments();
    hal.driver_cap.no_gcode_message_handling = true;
    char input[] = "g90(MSG,Change tool)";
    char *message = NULL; status_code_t status = Status_OK;
    CHECK(strcmp(gc_normalize_block(input, &status, &message), "G90") == 0);
    CHECK(status == Status_OK && !message && !process_comment_calls);
    CHECK(plain_comment_calls == 1 && strcmp(captured_comment, "MSG,Change tool") == 0);
    return EXIT_SUCCESS;
}
