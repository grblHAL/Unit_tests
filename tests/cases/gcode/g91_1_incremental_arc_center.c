#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G90 G91.1 - Absolute mode with incremental arc center
    char block1[] = "G90G91.1";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.distance == DistanceMode_Absolute);
    // G91.1 makes IJK incremental

    // G2 X10 Y10 I5 J0 - Arc with incremental center
    char block2[] = "G2X10Y10I5J0F100";
    CHECK(gc_execute_block(block2) == Status_OK);

    // G90 G90.1 - Cancel incremental arc center
    char block3[] = "G90G90.1";
    CHECK(gc_execute_block(block3) == Status_OK);

    return EXIT_SUCCESS;
}