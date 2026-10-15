#include "support/build_report_host.h"
int main(void)
{
    prepare_build_report();
    spindle_get(0)->cap.variable = true;
    build_report(true);
    CHECK(strstr(engine_output, "[OPT:VN") != NULL);
    return EXIT_SUCCESS;
}
