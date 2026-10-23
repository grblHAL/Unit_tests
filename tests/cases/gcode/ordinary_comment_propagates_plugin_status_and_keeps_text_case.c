#include "support/gcode_comment_host.h"
int main(void)
{
    prepare_gcode_comments();
    plain_comment_status = Status_UserException;
    char input[] = "g90(Comment With Case)";
    char *message = NULL; status_code_t status = Status_OK;
    CHECK(*gc_normalize_block(input, &status, &message) == '\0');
    CHECK(status == Status_UserException && message == NULL);
    CHECK(plain_comment_calls == 1 && strcmp(captured_comment, "Comment With Case") == 0);
    return EXIT_SUCCESS;
}
