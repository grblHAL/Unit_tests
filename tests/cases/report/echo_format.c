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
    char line[] = "G1X10";
    report_echo_line_received(line);
    CHECK(strcmp(engine_output, "[echo: G1X10]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
