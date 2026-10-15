#include "support/build_report_host.h"
int main(void)
{
    prepare_build_report();
    settings.homing.flags.enabled = true;
    settings.homing.cycle[0].mask = AXES_BITMASK;
    build_report(true);
    CHECK(strstr(engine_output, ",HOME,") != NULL);
    return EXIT_SUCCESS;
}
