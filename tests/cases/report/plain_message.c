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
    report_message("Ready", Message_Plain);
    CHECK(strcmp(engine_output, "[MSG:Ready]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
