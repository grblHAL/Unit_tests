#include "support/engine_host.h"
#include "protocol.h"
#include "check.h"
static unsigned unknown_calls;
static const uint8_t plugin_commands[] = {1, 0x1f, 0xaf, 0xbf};
static bool consume_unknown(char byte)
{
    CHECK(unknown_calls < sizeof(plugin_commands));
    CHECK((uint8_t)byte == plugin_commands[unknown_calls]);
    unknown_calls++;
    return true;
}
int main(void)
{
    engine_prepare();
    grbl.on_unknown_realtime_cmd = consume_unknown;
    for(unsigned i = 0; i < sizeof(plugin_commands); i++)
        CHECK(protocol_enqueue_realtime_command((char)plugin_commands[i]));
    CHECK(unknown_calls == sizeof(plugin_commands));
    const uint8_t sender_bytes[] = {' ', 'G', '1', 'X', '2', ASCII_DEL};
    for(unsigned i = 0; i < sizeof(sender_bytes); i++)
        CHECK(!protocol_enqueue_realtime_command((char)sender_bytes[i]));
    CHECK(unknown_calls == sizeof(plugin_commands));
    CHECK(sys.rt_exec_state == 0 && !sys.abort);
    return EXIT_SUCCESS;
}
