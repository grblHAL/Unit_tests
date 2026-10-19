#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G90 G10 L2 P1 X10 Y20 - Absolute offset
    char block1[] = "G90G10L2P1X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);
    coord_system_data_t *g54 = settings_get_coord_data(CoordinateSystem_G54);
    NEAR(g54->offset[0], 10.0f);
    NEAR(g54->offset[1], 20.0f);

    // G91 G10 L2 P1 X5 Y5 - Incremental offset (adds to existing)
    char block2[] = "G91G10L2P1X5Y5";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(g54->offset[0], 15.0f);
    NEAR(g54->offset[1], 25.0f);

    // G90 G10 L20 P1 X5 Y5 - Absolute relative offset
    char block3[] = "G90G10L20P1X5Y5";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(g54->offset[0], 20.0f);
    NEAR(g54->offset[1], 30.0f);

    // G91 G10 L20 P1 X5 Y5 - Incremental relative offset
    char block4[] = "G91G10L20P1X5Y5";
    CHECK(gc_execute_block(block4) == Status_OK);
    NEAR(g54->offset[0], 25.0f);
    NEAR(g54->offset[1], 35.0f);

    return EXIT_SUCCESS;
}