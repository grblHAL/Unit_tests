#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G10 L2 P1 X10 Y20 - Set G54 work offset
    char block1[] = "G10L2P1X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);
    coord_system_data_t *g54 = settings_get_coord_data(CoordinateSystem_G54);
    NEAR(g54->offset[0], 10.0f);
    NEAR(g54->offset[1], 20.0f);

    // G10 L2 P2 X5 Y5 R90 - Set G55 with 90 degree rotation
    char block2[] = "G10L2P2X5Y5R90";
    CHECK(gc_execute_block(block2) == Status_OK);
    coord_system_data_t *g55 = settings_get_coord_data(CoordinateSystem_G55);
    NEAR(g55->offset[0], 5.0f);
    NEAR(g55->offset[1], 5.0f);
    NEAR(g55->rotation, 90.0f);

    // G10 L20 P1 X1 Y1 - Set G54 relative offset (adds to existing)
    char block3[] = "G10L20P1X1Y1";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(g54->offset[0], 11.0f);
    NEAR(g54->offset[1], 21.0f);

    // G10 L2 P6 - Invalid coordinate system (only G54-G59.3 supported)
    char block4[] = "G10L2P6X0Y0";
    CHECK(gc_execute_block(block4) == Status_GcodeCoordinateSystem);

    return EXIT_SUCCESS;
}