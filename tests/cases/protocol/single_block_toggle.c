#include "support/engine_host.h"
#include "protocol.h"
#include "override.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    CHECK(protocol_enqueue_realtime_command(CMD_SINGLE_BLOCK_TOGGLE));
    CHECK(sys.flags.single_block);
    CHECK(protocol_enqueue_realtime_command(CMD_SINGLE_BLOCK_TOGGLE));
    CHECK(!sys.flags.single_block);
    return EXIT_SUCCESS;
}
