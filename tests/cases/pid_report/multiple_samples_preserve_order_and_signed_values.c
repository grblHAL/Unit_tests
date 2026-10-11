#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    sys.pid_log.idx = 3;
    sys.pid_log.target[0] = -1.5f;
    sys.pid_log.actual[0] = -1.25f;
    sys.pid_log.target[1] = 0;
    sys.pid_log.actual[1] = 0.125f;
    sys.pid_log.target[2] = 2.5f;
    sys.pid_log.actual[2] = 2.25f;
    report_pid_log();
    CHECK(strcmp(engine_output, "[PID:0.000,0.000,2|-1.500,-1.250,0.000,0.125,2.500,2.250]" ASCII_EOL "ok" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
