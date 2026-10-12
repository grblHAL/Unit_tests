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
    char line[] = "G21";
    report_execute_startup_message(line, Status_OK);
    CHECK(strcmp(engine_output, ">G21:ok" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
