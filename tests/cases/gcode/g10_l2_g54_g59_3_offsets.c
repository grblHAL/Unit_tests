#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G10L2P1X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);
    char block2[] = "G10L2P2X5Y5";
    CHECK(gc_execute_block(block2) == Status_OK);
    char block3[] = "G10L2P3X15Y15";
    CHECK(gc_execute_block(block3) == Status_OK);
    char block4[] = "G10L2P4X20Y20";
    CHECK(gc_execute_block(block4) == Status_OK);
    char block5[] = "G10L2P5X25Y25";
    CHECK(gc_execute_block(block5) == Status_OK);
    char block6[] = "G10L2P6X30Y30";
    CHECK(gc_execute_block(block6) == Status_OK);
    char block7[] = "G10L2P7X35Y35";
    CHECK(gc_execute_block(block7) == Status_OK);
    char block8[] = "G10L2P8X40Y40";
    CHECK(gc_execute_block(block8) == Status_OK);
    char block9[] = "G10L2P9X45Y45";
    CHECK(gc_execute_block(block9) == Status_OK);
    char block10[] = "G10L2P10X0Y0";
    CHECK(gc_execute_block(block10) == Status_GcodeUnsupportedCoordSys);

    return EXIT_SUCCESS;
}
