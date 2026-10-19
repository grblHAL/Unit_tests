#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G20 - Inch mode
    char block1[] = "G20";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.units_imperial == true);

    // G21 - Metric mode
    char block2[] = "G21";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(gc_state.modal.units_imperial == false);

    // G20 G1 X1.0 F10 - 1 inch move
    char block3[] = "G20G1X1.0F10";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.position[0], 25.4f); // 1 inch = 25.4 mm

    // G21 G1 X25.4 F10 - 25.4 mm move
    char block4[] = "G21G1X25.4F10";
    CHECK(gc_execute_block(block4) == Status_OK);
    NEAR(gc_state.position[0], 50.8f); // 25.4 + 25.4 mm

    return EXIT_SUCCESS;
}