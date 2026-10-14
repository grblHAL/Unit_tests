#include "support/accessory_report_host.h"

int main(void)
{
    prepare_accessory_report();
    accessory_coolant.flood = true;
    emit_accessory_report();
    CHECK(strstr(engine_output, "|A:F>") != NULL);
    return EXIT_SUCCESS;
}
