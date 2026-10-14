#include "support/accessory_report_host.h"

int main(void)
{
    prepare_accessory_report();
    accessory_spindle.on = true;
    emit_accessory_report();
    CHECK(strstr(engine_output, "|A:S>") != NULL);
    return EXIT_SUCCESS;
}
