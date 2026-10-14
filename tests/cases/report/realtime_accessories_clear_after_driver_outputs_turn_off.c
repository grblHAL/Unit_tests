#include "support/accessory_report_host.h"

int main(void)
{
    prepare_accessory_report();
    accessory_spindle.on = true;
    accessory_coolant.flood = true;
    emit_accessory_report(); CHECK(strstr(engine_output, "|A:SF>") != NULL);
    accessory_spindle.on = false; accessory_coolant.flood = false;
    engine_output[0] = 0;
    emit_accessory_report();
    CHECK(strstr(engine_output, "|A:>") != NULL);
    return EXIT_SUCCESS;
}
