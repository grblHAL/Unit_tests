#include "vinput_host.h"
int main(void)
{
    vi_start(true);
    CHECK(!grbl.on_unknown_realtime_cmd((char)0xB8));
    unknown_result = true;
    CHECK(grbl.on_unknown_realtime_cmd((char)0xB8));
    CHECK(unknown_calls == 2);
    CHECK(grbl.on_unknown_realtime_cmd((char)CMD_VINPUT_TLS_SET));
    CHECK(unknown_calls == 2);
    return 0;
}
