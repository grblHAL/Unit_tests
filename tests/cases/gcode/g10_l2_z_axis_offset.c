#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G10 L2 P1 Z10 - Set Z offset in G54
    char block1[] = "G10L2P1Z10";
    CHECK(gc_execute_block(block1) == Status_OK);
    coord_system_data_t *g54 = settings_get_coord_data(CoordinateSystem_G54);
    NEAR(g54->offset[2], 10.0f);

    // G10 L2 P1 X5 Y5 Z5 - Set all axes
    char block2[] = "G10L2P1X5Y5Z5";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(g54->offset[0], 5.0f);
    NEAR(g54->offset[1], 5.0f);
    NEAR(g54->offset[2], 5.0f);

    // G10 L2 P1 A10 B20 C30 - Rotary axes (if supported)
    char block3[] = "G10L2P1A10B20C30";
    CHECK(gc_execute_block(block3) == Status_OK);
    // Note: A/B/C may map to different axes depending on configuration

    return EXIT_SUCCESS;
}