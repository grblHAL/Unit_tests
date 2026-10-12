#include "support/spindle_slot_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_mapped_spindles();
    CHECK(report_spindles(false) == Status_OK);
    CHECK(strcmp(engine_output, "0 - primary, enabled as spindle 0" ASCII_EOL
                               "1 - secondary, enabled as spindle 1" ASCII_EOL
                               "2 - auxiliary" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
