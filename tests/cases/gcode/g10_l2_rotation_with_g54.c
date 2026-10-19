#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G10 L2 P1 X10 Y20 R90 - Set G54 offset with 90 degree rotation
    char block1[] = "G10L2P1X10Y20R90";
    CHECK(gc_execute_block(block1) == Status_OK);
    coord_system_data_t *g54 = settings_get_coord_data(CoordinateSystem_G54);
    NEAR(g54->offset[0], 10.0f);
    NEAR(g54->offset[1], 20.0f);
    NEAR(g54->rotation, 90.0f);

    // G10 L2 P1 X5 Y5 R45 - Update G54 offset and rotation
    char block2[] = "G10L2P1X5Y5R45";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(g54->offset[0], 5.0f);
    NEAR(g54->offset[1], 5.0f);
    NEAR(g54->rotation, 45.0f);

    // G10 L2 P1 R0 - Clear rotation
    char block3[] = "G10L2P1R0";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(g54->rotation, 0.0f);

    return EXIT_SUCCESS;
}