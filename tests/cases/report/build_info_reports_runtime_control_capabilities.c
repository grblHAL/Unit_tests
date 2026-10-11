#include "support/build_report_host.h"
#include "check.h"

int main(void)
{
    prepare_build_report();
    hal.signals_cap.stop_disable = true;
    hal.signals_cap.block_delete = true;
    hal.signals_cap.e_stop = true;
    hal.driver_cap.mpg_mode = true;
    hal.driver_cap.spindle_sync = true;
    hal.driver_cap.rtc = true;
    build_report(true);
    CHECK(strstr(engine_output, ",OS,") != NULL);
    CHECK(strstr(engine_output, ",BD,") != NULL);
    CHECK(strstr(engine_output, ",ES,") != NULL);
    CHECK(strstr(engine_output, ",MPG,") != NULL);
    CHECK(strstr(engine_output, ",SS,") != NULL);
    CHECK(strstr(engine_output, ",RTC]") != NULL);
    return EXIT_SUCCESS;
}
