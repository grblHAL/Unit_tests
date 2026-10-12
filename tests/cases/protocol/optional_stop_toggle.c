#include "support/engine_host.h"
#include "protocol.h"
#include "override.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    CHECK(protocol_enqueue_realtime_command(CMD_OPTIONAL_STOP_TOGGLE));
    CHECK(sys.flags.optional_stop_disable);
    CHECK(protocol_enqueue_realtime_command(CMD_OPTIONAL_STOP_TOGGLE));
    CHECK(!sys.flags.optional_stop_disable);
    return EXIT_SUCCESS;
}
