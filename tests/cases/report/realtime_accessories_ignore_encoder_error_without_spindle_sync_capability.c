#include "support/accessory_report_host.h"

int main(void)
{
    prepare_accessory_report();
    hal.driver_cap.spindle_sync = false;
    accessory_spindle.encoder_error = true;
    emit_accessory_report();
    CHECK(strstr(engine_output, "|A:>") != NULL);
    return EXIT_SUCCESS;
}
