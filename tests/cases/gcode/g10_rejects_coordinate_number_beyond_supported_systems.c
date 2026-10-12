#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char block[] = "G10L2P10X10";
    CHECK(gc_execute_block(block) == Status_GcodeUnsupportedCoordSys);
    NEAR(gc_state.modal.g5x_offset.data.coord.x, 0);
    return EXIT_SUCCESS;
}
