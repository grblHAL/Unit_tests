#include "support/accessory_report_host.h"

int main(void)
{
    prepare_accessory_report();
    accessory_spindle.on = accessory_spindle.ccw = true;
    accessory_coolant.flood = accessory_coolant.mist = true;
    emit_accessory_report();
    CHECK(strstr(engine_output, "|A:CFM>") != NULL);
    return EXIT_SUCCESS;
}
