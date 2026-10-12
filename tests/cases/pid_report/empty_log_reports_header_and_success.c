#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    sys.pid_log.setpoint = 100;
    sys.pid_log.t_sample = 0.125f;
    report_pid_log();
    CHECK(strcmp(engine_output, "[PID:100.000,0.125,2|]" ASCII_EOL "ok" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
