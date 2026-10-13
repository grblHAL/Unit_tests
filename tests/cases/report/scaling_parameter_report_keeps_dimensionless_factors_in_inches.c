#include "support/scaling_parameter_report_host.h"

int main(void)
{
    prepare_report();
    char scale[] = "G51X2Y3Z4";
    CHECK(gc_execute_block(scale) == Status_OK);
    settings.flags.report_inches = true;
    report_init();
    check_scaling_parameter_report();
    return EXIT_SUCCESS;
}
