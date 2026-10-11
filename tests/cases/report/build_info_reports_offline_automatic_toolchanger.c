#include "support/build_report_host.h"
#include "check.h"

int main(void)
{
    prepare_build_report();
    build_atc_state = ATC_Offline;
    build_report(true);
    CHECK(strstr(engine_output, ",ATC=0,") != NULL);
    CHECK(strstr(engine_output, ",ATC=1,") == NULL);
    return EXIT_SUCCESS;
}
