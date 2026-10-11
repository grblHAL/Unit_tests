#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    sys.pid_log.setpoint = 50;
    sys.pid_log.t_sample = 0.25f;
    sys.pid_log.idx = 1;
    sys.pid_log.target[0] = 12.5f;
    sys.pid_log.actual[0] = 12.25f;
    report_pid_log();
    CHECK(strcmp(engine_output, "[PID:50.000,0.250,2|12.500,12.250]" ASCII_EOL "ok" ASCII_EOL) == 0);
    CHECK(sys.pid_log.idx == 1);
    NEAR(sys.pid_log.target[0], 12.5f);
    NEAR(sys.pid_log.actual[0], 12.25f);
    return EXIT_SUCCESS;
}
