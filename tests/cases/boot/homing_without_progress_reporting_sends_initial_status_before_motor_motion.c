#include "support/boot_router_homing_host.h"
int main(void)
{
    router_report_progress = false;
    run_router_homing();
    CHECK(strstr(engine_output, "<Home|") != NULL);
    return EXIT_SUCCESS;
}
