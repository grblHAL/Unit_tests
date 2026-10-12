#include "support/report_host.h"
#include "check.h"

int main(void)
{
    prepare_report();
    sys.pid_log.idx = PID_LOG;
    for(unsigned i = 0; i < PID_LOG; i++) {
        sys.pid_log.target[i] = (float)i;
        sys.pid_log.actual[i] = (float)i + 0.5f;
    }
    report_pid_log();
    CHECK(strcmp(engine_output, "[PID:0.000,0.000,2|0.000,0.500,1.000,1.500,2.000,2.500,3.000,3.500,4.000,4.500,5.000,5.500,6.000,6.500,7.000,7.500]" ASCII_EOL "ok" ASCII_EOL) == 0);
    CHECK(sys.pid_log.idx == PID_LOG);
    return EXIT_SUCCESS;
}
