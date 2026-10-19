#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G10 L2 P1 X10 Y20 - G54
    char block1[] = "G10L2P1X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);

    // G10 L2 P2 X5 Y5 - G55
    char block2[] = "G10L2P2X5Y5";
    CHECK(gc_execute_block(block2) == Status_OK);

    // G10 L2 P3 X15 Y15 - G56
    char block3[] = "G10L2P3X15Y15";
    CHECK(gc_execute_block(block3) == Status_OK);

    // G10 L2 P4 X20 Y20 - G57
    char block4[] = "G10L2P4X20Y20";
    CHECK(gc_execute_block(block4) == Status_OK);

    // G10 L2 P5 X25 Y25 - G58
    char block5[] = "G10L2P5X25Y25";
    CHECK(gc_execute_block(block5) == Status_OK);

    // G10 L2 P6 X30 Y30 - G59
    char block6[] = "G10L2P6X30Y30";
    CHECK(gc_execute_block(block6) == Status_OK);

    // G10 L2 P7 X35 Y35 - G59.1
    char block7[] = "G10L2P7X35Y35";
    CHECK(gc_execute_block(block7) == Status_OK);

    // G10 L2 P8 X40 Y40 - G59.2
    char block8[] = "G10L2P8X40Y40";
    CHECK(gc_execute_block(block8) == Status_OK);

    // G10 L2 P9 X45 Y45 - G59.3
    char block9[] = "G10L2P9X45Y45";
    CHECK(gc_execute_block(block9) == Status_OK);

    // G10 L2 P10 - Invalid (only 1-9)
    char block10[] = "G10L2P10X0Y0";
    CHECK(gc_execute_block(block10) == Status_GcodeCoordinateSystem);

    return EXIT_SUCCESS;
}