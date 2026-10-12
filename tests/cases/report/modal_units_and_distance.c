#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    char block[] = "G20G91";
    CHECK(gc_execute_block(block) == Status_OK);
    report_gcode_modes(hal.stream.write);
    CHECK(strncmp(engine_output, "[GC:", 4) == 0);
    CHECK(strstr(engine_output, " G20 G91 ") != NULL);
    CHECK(strstr(engine_output, " M5 M9 ") != NULL);
    CHECK(strstr(engine_output, "]" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
