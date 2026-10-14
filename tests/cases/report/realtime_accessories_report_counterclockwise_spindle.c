#include "support/accessory_report_host.h"

int main(void)
{
    prepare_accessory_report();
    accessory_spindle.on = accessory_spindle.ccw = true;
    emit_accessory_report();
    CHECK(strstr(engine_output, "|A:C>") != NULL);
    return EXIT_SUCCESS;
}
