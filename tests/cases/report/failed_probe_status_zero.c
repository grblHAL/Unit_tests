#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    sys.flags.probe_succeeded = false;
    report_probe_parameters();
    CHECK(strcmp(engine_output, "[PRB:0.000,0.000,0.000:0]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
