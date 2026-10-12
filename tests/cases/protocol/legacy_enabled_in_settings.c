#include "support/engine_host.h"
#include "protocol.h"
#include "override.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    settings.flags.legacy_rt_commands = true;
    CHECK(!protocol_enqueue_realtime_command('$'));
    CHECK(protocol_enqueue_realtime_command(CMD_STATUS_REPORT_LEGACY));
    CHECK(sys.rt_exec_state == EXEC_STATUS_REPORT);
    return EXIT_SUCCESS;
}
