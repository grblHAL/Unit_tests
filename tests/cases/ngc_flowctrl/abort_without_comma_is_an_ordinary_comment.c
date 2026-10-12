#include "support/flow_comment_host.h"
#include "check.h"

int main(void)
{
    prepare_flow_comment();
    char comment[] = "ABORT";
    CHECK(grbl.on_gcode_comment(comment) == Status_OK);
    CHECK(prior_comment_calls == 1 && process_comment_calls == 0);
    CHECK(engine_output[0] == '\0');
    return EXIT_SUCCESS;
}
