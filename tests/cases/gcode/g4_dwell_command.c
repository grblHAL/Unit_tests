#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G4P1.0";
    CHECK(gc_execute_block(block1) == Status_OK);
    char block2[] = "G4P0";
    CHECK(gc_execute_block(block2) == Status_OK);
    char block3[] = "G4";
    CHECK(gc_execute_block(block3) == Status_GcodeValueWordMissing);
    char block4[] = "G4P-1";
    CHECK(gc_execute_block(block4) == Status_NegativeValue);

    return EXIT_SUCCESS;
}
