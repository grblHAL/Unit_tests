#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char block[] = "G10L3P1X10";
    CHECK(gc_execute_block(block) == Status_GcodeUnsupportedCommand);
    NEAR(gc_state.modal.g5x_offset.data.coord.x, 0);
    return EXIT_SUCCESS;
}
