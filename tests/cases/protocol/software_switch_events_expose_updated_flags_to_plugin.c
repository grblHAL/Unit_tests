#include "support/engine_host.h"
#include "protocol.h"
#include "check.h"
static unsigned events;
static void switch_event(control_signals_t signals)
{
    if(events < 2) {
        CHECK(signals.stop_disable && !signals.single_block);
        CHECK(sys.flags.optional_stop_disable == (events == 0));
    } else {
        CHECK(signals.single_block && !signals.stop_disable);
        CHECK(sys.flags.single_block == (events == 2));
    }
    events++;
}
int main(void)
{
    engine_prepare();
    grbl.on_control_signals_changed = switch_event;
    CHECK(protocol_enqueue_realtime_command(CMD_OPTIONAL_STOP_TOGGLE));
    CHECK(protocol_enqueue_realtime_command(CMD_OPTIONAL_STOP_TOGGLE));
    CHECK(protocol_enqueue_realtime_command(CMD_SINGLE_BLOCK_TOGGLE));
    CHECK(protocol_enqueue_realtime_command(CMD_SINGLE_BLOCK_TOGGLE));
    CHECK(events == 4);
    CHECK(!sys.flags.optional_stop_disable && !sys.flags.single_block);
    return EXIT_SUCCESS;
}
