#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G4 P1.0 - Dwell 1 second
    char block1[] = "G4P1.0";
    CHECK(gc_execute_block(block1) == Status_OK);

    // G4 P0.5 - Dwell 0.5 seconds
    char block2[] = "G4P0.5";
    CHECK(gc_execute_block(block2) == Status_OK);

    // G4 P0 - Dwell 0 seconds
    char block3[] = "G4P0";
    CHECK(gc_execute_block(block3) == Status_OK);

    // G4 with X word (some dialects use X for dwell)
    // Not standard in grblHAL

    return EXIT_SUCCESS;
}