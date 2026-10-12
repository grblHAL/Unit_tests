#include "support/engine_host.h"
#include "protocol.h"
#include "override.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    settings.report_interval = 100;
    CHECK(protocol_enqueue_realtime_command(CMD_AUTO_REPORTING_TOGGLE));
    CHECK(sys.flags.auto_reporting);
    CHECK(protocol_enqueue_realtime_command(CMD_AUTO_REPORTING_TOGGLE));
    CHECK(!sys.flags.auto_reporting);
    return EXIT_SUCCESS;
}
