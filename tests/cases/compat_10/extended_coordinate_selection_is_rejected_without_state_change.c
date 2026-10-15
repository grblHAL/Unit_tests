#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char block[] = "G59.3";
    CHECK(gc_execute_block(block) == Status_GcodeUnsupportedCommand);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G54);
    return EXIT_SUCCESS;
}
