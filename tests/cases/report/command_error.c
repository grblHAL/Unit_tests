#include "support/engine_host.h"
#include "report.h"
#include <string.h>
#include "check.h"
static bool connected(void) { return true; }
int main(void)
{
    engine_prepare();
    hal.stream.is_connected = connected;
    report_init_fns();
    report_init();
    CHECK(grbl.report.status_message(Status_BadNumberFormat) == Status_BadNumberFormat);
    CHECK(strcmp(engine_output, "error:2" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
