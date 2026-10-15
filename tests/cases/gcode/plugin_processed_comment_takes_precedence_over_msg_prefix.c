#include "support/gcode_comment_host.h"
int main(void)
{
    prepare_gcode_comments();
    plugin_message = "Plugin tool prompt";
    char input[] = "G90(MSG,original)";
    char *message = NULL; status_code_t status = Status_OK;
    CHECK(strcmp(gc_normalize_block(input, &status, &message), "G90") == 0);
    CHECK(status == Status_OK && message && strcmp(message, plugin_message) == 0);
    CHECK(process_comment_calls == 1 && plain_comment_calls == 0);
    free(message);
    char program[] = "(MSG,original)";
    CHECK(gc_execute_block(program) == Status_OK);
    CHECK(strstr(engine_output, "Plugin tool prompt") != NULL);
    CHECK(strstr(engine_output, "original") == NULL);
    return EXIT_SUCCESS;
}
