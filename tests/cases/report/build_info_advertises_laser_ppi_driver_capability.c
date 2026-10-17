#include "support/build_report_host.h"
int main(void)
{
    prepare_build_report();
    build_report(true);
    CHECK(strstr(engine_output, "PPI,") == NULL);
    engine_output[0] = '\0';
    hal.driver_cap.laser_ppi_mode = true;
    build_report(true);
    CHECK(strstr(engine_output, "PPI,") != NULL);
    return EXIT_SUCCESS;
}
