#include "support/flow_comment_host.h"
#include "check.h"

int main(void)
{
    prepare_flow_comment();
    char comment[] = "aBoRt,lowercase";
    CHECK(grbl.on_gcode_comment(comment) == Status_UserException);
    CHECK(strcmp(engine_output, "[MSG:Error: lowercase]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
