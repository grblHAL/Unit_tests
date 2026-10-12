#include "support/flow_comment_host.h"
#include "check.h"

int main(void)
{
    prepare_flow_comment();
    processed_message = "plugin explanation";
    char comment[] = "ABORT,original explanation";
    CHECK(grbl.on_gcode_comment(comment) == Status_UserException);
    CHECK(process_comment_calls == 1 && prior_comment_calls == 0);
    CHECK(strcmp(engine_output, "[MSG:Error: plugin explanation]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
