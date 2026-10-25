#include "support/engine_host.h"
#include "report.h"
#include <string.h>
#include "check.h"
static bool sender_connected = true;
static bool connected(void) { return sender_connected; }
int main(void)
{
    engine_prepare();
    hal.stream.is_connected = connected;
    report_init_fns();
    report_init();
    char line[] = "G21";
    report_execute_startup_message(line, Status_OK);
    CHECK(strcmp(engine_output, ">G21:ok" ASCII_EOL) == 0);
    engine_output[0] = 0;
    sender_connected = false;
    report_execute_startup_message(line, Status_BadNumberFormat);
    CHECK(engine_output[0] == 0);
    sender_connected = true;
    report_execute_startup_message(line, Status_BadNumberFormat);
    CHECK(strcmp(engine_output, ">G21:error:2" ASCII_EOL) == 0);
    engine_output[0] = 0;
    report_execute_startup_message(line, Status_OK);
    CHECK(strcmp(engine_output, ">G21:ok" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
