#include "support/build_report_host.h"
#include "check.h"

int main(void)
{
    prepare_build_report();
    hal.probe.get_state = NULL;
    build_report(true);
    CHECK(strstr(engine_output, ",NOPROBE,") != NULL);
    return EXIT_SUCCESS;
}
