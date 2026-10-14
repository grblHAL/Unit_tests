#include "support/accessory_report_host.h"

int main(void)
{
    prepare_accessory_report();
    accessory_coolant.mist = true;
    emit_accessory_report();
    CHECK(strstr(engine_output, "|A:M>") != NULL);
    return EXIT_SUCCESS;
}
