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
    char line[] = "G21G90";
    report_startup_line(1, line);
    CHECK(strcmp(engine_output, "$N1=G21G90" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
