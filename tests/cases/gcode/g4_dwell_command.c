#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G4 P1.0 - Dwell for 1 second
    char block1[] = "G4P1.0";
    CHECK(gc_execute_block(block1) == Status_OK);

    // G4 P0 - Dwell for 0 seconds (should be valid)
    char block2[] = "G4P0";
    CHECK(gc_execute_block(block2) == Status_OK);

    // G4 without P - Should fail
    char block3[] = "G4";
    CHECK(gc_execute_block(block3) == Status_GcodeValueWordMissing);

    // G4 P-1 - Negative dwell should fail
    char block4[] = "G4P-1";
    CHECK(gc_execute_block(block4) == Status_NegativeValue);

    return EXIT_SUCCESS;
}