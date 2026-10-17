#include "support/queued_motion_rejection_host.h"
static unsigned comments;
static status_code_t reject_note(char *text)
{
    CHECK(strcmp(text, "Plugin validation") == 0);
    comments++;
    return Status_UserException;
}
int main(void)
{
    prepare_motion_program();
    queue_motion_program("G1X1F100");
    grbl.on_gcode_comment = reject_note;
    check_rejected_block_preserves_queued_motion("G20G91G1X2F50(Plugin validation)", Status_UserException);
    CHECK(comments == 1);
    return EXIT_SUCCESS;
}
