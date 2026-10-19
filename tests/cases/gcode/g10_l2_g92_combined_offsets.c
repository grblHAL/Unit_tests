#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G10 L2 P1 X10 Y20 - Set G54 offset
    char block1[] = "G10L2P1X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);
    coord_system_data_t *g54 = settings_get_coord_data(CoordinateSystem_G54);
    NEAR(g54->offset[0], 10.0f);
    NEAR(g54->offset[1], 20.0f);

    // G92 X5 Y5 - Set G92 offset
    char block2[] = "G92X5Y5";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.g92_offset[0], -5.0f);
    NEAR(gc_state.g92_offset[1], -5.0f);

    // Position should be G54 + G92
    char block3[] = "G0X0Y0";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.position[0], 15.0f); // 10 + 5
    NEAR(gc_state.position[1], 25.0f); // 20 + 5

    // G92.1 - Reset G92
    char block4[] = "G92.1";
    CHECK(gc_execute_block(block4) == Status_OK);
    NEAR(gc_state.g92_offset[0], 0.0f);
    NEAR(gc_state.g92_offset[1], 0.0f);

    // Position should be just G54
    char block5[] = "G0X0Y0";
    CHECK(gc_execute_block(block5) == Status_OK);
    NEAR(gc_state.position[0], 10.0f);
    NEAR(gc_state.position[1], 20.0f);

    return EXIT_SUCCESS;
}