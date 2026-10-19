#include "support/build_report_host.h"
static unsigned reboot_calls;
static void reboot_driver(void) { reboot_calls++; }
int main(void)
{
    prepare_build_report();
    build_report(true);
    CHECK(strstr(engine_output, "REBOOT,") == NULL);
    engine_output[0] = '\0';
    hal.reboot = reboot_driver;
    build_report(true);
    CHECK(strstr(engine_output, "REBOOT,") != NULL);
    CHECK(reboot_calls == 0);
    return EXIT_SUCCESS;
}
