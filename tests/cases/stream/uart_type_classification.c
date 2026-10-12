#include "support/engine_host.h"
#include "stream.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    CHECK(stream_is_uart(StreamType_Serial));
    CHECK(stream_is_uart(StreamType_Bluetooth));
    CHECK(!stream_is_uart(StreamType_Null));
    return EXIT_SUCCESS;
}
