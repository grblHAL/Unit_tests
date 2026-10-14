#include "support/debug_serial_host.h"
int main(void)
{
    prepare_debug_serial();
    debug_property.type = StreamType_Telnet;
    CHECK(!debug_stream_init());
    CHECK(debug_claim_calls == 0);
    CHECK(debug_output[0] == 0);
    return 0;
}
