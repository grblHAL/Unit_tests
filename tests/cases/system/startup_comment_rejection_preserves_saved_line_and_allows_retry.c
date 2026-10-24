#include "support/system_command_host.h"
static unsigned comments;
static status_code_t reject_startup_comment(char *comment)
{
    CHECK(strcmp(comment, "Keep Case") == 0);
    comments++;
    fputs("startup-comment-rejection: returning plugin error\n", stderr);
    fflush(stderr);
    return Status_UserException;
}
int main(void)
{
    prepare_system_command();
    stored_line_t original = "G90", actual;
    settings_write_startup_line(0, original);
    grbl.on_gcode_comment = reject_startup_comment;
    CHECK(system_command("$N0=G91(Keep Case)") == Status_UserException);
    CHECK(comments == 1);
    CHECK(settings_read_startup_line(0, actual) && strcmp(actual, original) == 0);
    CHECK(!gc_state.modal.distance_incremental && state_get() == STATE_IDLE);
    grbl.on_gcode_comment = NULL;
    CHECK(system_command("$N0=G91") == Status_OK);
    CHECK(settings_read_startup_line(0, actual) && strcmp(actual, "G91") == 0);
    return EXIT_SUCCESS;
}
