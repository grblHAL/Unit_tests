#include "support/gcode_comment_host.h"
int main(void)
{
    prepare_gcode_comments();
    sys.flags.block_delete_enabled = true;
    char input[] = " /g90(MSG,Change tool)";
    char *message = NULL; status_code_t status = Status_OK;
    CHECK(*gc_normalize_block(input, &status, &message) == '\0');
    CHECK(status == Status_OK && !message);
    CHECK(!plain_comment_calls && !process_comment_calls);
    return EXIT_SUCCESS;
}
