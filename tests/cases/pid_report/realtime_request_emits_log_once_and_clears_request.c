#include "support/report_host.h"
#include "protocol.h"
#include "override.h"
#include "check.h"

int main(void)
{
    prepare_report();
    grbl.on_execute_realtime = protocol_execute_noop;
    sys.pid_log.idx = 1;
    sys.pid_log.target[0] = 3;
    sys.pid_log.actual[0] = 2;
    CHECK(protocol_enqueue_realtime_command(CMD_PID_REPORT));
    CHECK(sys.rt_exec_state & EXEC_PID_REPORT);
    CHECK(protocol_exec_rt_system());
    CHECK(!(sys.rt_exec_state & EXEC_PID_REPORT));
    CHECK(strcmp(engine_output, "[PID:0.000,0.000,2|3.000,2.000]" ASCII_EOL "ok" ASCII_EOL) == 0);
    engine_output[0] = 0;
    CHECK(protocol_exec_rt_system());
    CHECK(engine_output[0] == 0);
    return EXIT_SUCCESS;
}
