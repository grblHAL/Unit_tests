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
    char dry_run[] = "G91(MSG,Change tool)";
    CHECK(gc_execute_block(dry_run) == Status_OK);
    CHECK(gc_state.modal.distance_incremental);
    CHECK(gc_state.message == NULL && plan_get_current_block() == NULL);
    CHECK(!plain_comment_calls && !process_comment_calls && !message_output_calls);
    CHECK(engine_output[0] == '\0');
    return EXIT_SUCCESS;
}
