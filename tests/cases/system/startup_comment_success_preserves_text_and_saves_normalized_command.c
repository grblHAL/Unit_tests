#include "support/system_command_host.h"
static unsigned comments;
static status_code_t accept_startup_comment(char *comment)
{
    CHECK(strcmp(comment, "Keep Case") == 0);
    comments++;
    return Status_OK;
}
int main(void)
{
    prepare_system_command();
    grbl.on_gcode_comment = accept_startup_comment;
    CHECK(system_command("$N0=g91(Keep Case)") == Status_OK);
    stored_line_t actual;
    CHECK(settings_read_startup_line(0, actual) && strcmp(actual, "G91") == 0);
    CHECK(comments >= 1 && state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
