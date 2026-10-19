#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G20";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.units_imperial == true);
    char block2[] = "G21";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(gc_state.modal.units_imperial == false);
    char block3[] = "G20G1X1.0F10";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.position[0], 25.4f);
    char block4[] = "G21G1X25.4F10";
    CHECK(gc_execute_block(block4) == Status_OK);
    NEAR(gc_state.position[0], 25.4f);

    return EXIT_SUCCESS;
}
