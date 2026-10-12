#include "support/engine_host.h"
#include "report.h"
#include <string.h>
#include "check.h"
static bool connected(void) { return true; }
static bool disconnected(void) { return false; }
int main(void)
{
    engine_prepare();
    hal.stream.is_connected = connected;
    report_init_fns();
    report_init();
    hal.stream.is_connected = disconnected;
    CHECK(grbl.report.status_message(Status_BadNumberFormat) == Status_BadNumberFormat);
    CHECK(engine_output[0] == '\0');
    return EXIT_SUCCESS;
}
