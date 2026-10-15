#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    settings.homing.flags.enabled = true;
    report_ngc_parameters();
    CHECK(strstr(engine_output, "[HOME:") != NULL);
    CHECK(strstr(engine_output, "[G59:") != NULL);
    CHECK(strstr(engine_output, "[G59.3:") == NULL);
    CHECK(strstr(engine_output, "[G28:") != NULL && strstr(engine_output, "[G30:") != NULL);
    return EXIT_SUCCESS;
}
