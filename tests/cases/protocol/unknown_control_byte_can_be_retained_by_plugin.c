#include "support/engine_host.h"
#include "protocol.h"
#include "check.h"
static unsigned unknown_calls;
static bool retain_unknown(char byte) { CHECK(byte == 1); unknown_calls++; return false; }
int main(void)
{
    engine_prepare();
    grbl.on_unknown_realtime_cmd = retain_unknown;
    CHECK(!protocol_enqueue_realtime_command(1));
    CHECK(unknown_calls == 1);
    return EXIT_SUCCESS;
}
