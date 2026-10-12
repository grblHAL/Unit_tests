#include "support/report_host.h"
#include "stream.h"
#include "protocol.h"
#include "check.h"

int main(void)
{
    prepare_report();
    CHECK(hal.stream.enqueue_rt_command == NULL);
    CHECK(stream_enqueue_realtime_command(CMD_STATUS_REPORT));
    CHECK(sys.rt_exec_state & EXEC_STATUS_REPORT);
    return EXIT_SUCCESS;
}
