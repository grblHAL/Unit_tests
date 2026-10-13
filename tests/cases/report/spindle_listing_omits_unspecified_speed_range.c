#include "support/spindle_listing_report_host.h"

int main(void)
{
    prepare_spindle_listing();
    CHECK(report_spindles(true) == Status_OK);
    fprintf(stderr, "%s", engine_output);
    CHECK(strcmp(engine_output, "[SPINDLE:0|0|1|*|fixture spindle]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
