#include "support/build_report_host.h"
int main(void)
{
    prepare_build_report();
    build_report(true);
    CHECK(strstr(engine_output, ",CCMP,") != NULL);
    CHECK(strstr(engine_output, ",LATHE,LATHEUVW,") != NULL);
    return EXIT_SUCCESS;
}
