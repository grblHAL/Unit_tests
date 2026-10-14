#pragma once
#include "support/report_host.h"
static inline void modal_report_block(const char *source)
{
    char block[96]; CHECK(strlen(source) < sizeof(block)); strcpy(block, source);
    CHECK(gc_execute_block(block) == Status_OK);
    engine_output[0] = 0; report_gcode_modes(hal.stream.write);
}
