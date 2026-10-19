#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G54 G52 X5 Y5 - Set local coordinate system offset in G54
    char block1[] = "G54G52X5Y5";
    CHECK(gc_execute_block(block1) == Status_OK);
    coord_system_data_t *g54 = settings_get_coord_data(CoordinateSystem_G54);
    NEAR(g54->offset[0], 5.0f);
    NEAR(g54->offset[1], 5.0f);

    // G55 G52 X10 Y10 - Set local coordinate system offset in G55
    char block2[] = "G55G52X10Y10";
    CHECK(gc_execute_block(block2) == Status_OK);
    coord_system_data_t *g55 = settings_get_coord_data(CoordinateSystem_G55);
    NEAR(g55->offset[0], 10.0f);
    NEAR(g55->offset[1], 10.0f);

    // G52 X0 Y0 - Cancel local offset in current system
    char block3[] = "G52X0Y0";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(g55->offset[0], 0.0f);
    NEAR(g55->offset[1], 0.0f);

    return EXIT_SUCCESS;
}