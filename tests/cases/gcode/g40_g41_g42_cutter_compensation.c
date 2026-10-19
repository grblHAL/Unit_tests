#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G40 - Cancel cutter compensation (default)
    char block1[] = "G40";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.cutter_comp.side == CutterComp_Disable);

    // G41 - Cutter compensation left
    char block2[] = "G41D1";
    CHECK(gc_execute_block(block2) == Status_GcodeUnsupportedCommand); // Cutter comp not enabled in this build

    // G42 - Cutter compensation right
    char block3[] = "G42D1";
    CHECK(gc_execute_block(block3) == Status_GcodeUnsupportedCommand);

    return EXIT_SUCCESS;
}