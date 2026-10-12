#include "support/engine_host.h"
#include "protocol.h"
#include "override.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    sys.flags.auto_reporting = true;
    CHECK(protocol_enqueue_realtime_command(CMD_STATUS_REPORT));
    CHECK(sys.rt_exec_state == 0);
    return EXIT_SUCCESS;
}
