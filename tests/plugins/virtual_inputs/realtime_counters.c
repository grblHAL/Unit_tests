#include "vinput_host.h"
int main(void)
{
    vi_start(true);
    CHECK(grbl.on_unknown_realtime_cmd((char)CMD_VINPUT_PROBE_SET));
    CHECK(grbl.on_unknown_realtime_cmd((char)CMD_VINPUT_PROBE_SET));
    CHECK(grbl.on_unknown_realtime_cmd((char)CMD_VINPUT_TLS_SET));
    CHECK(grbl.on_unknown_realtime_cmd((char)CMD_VINPUT_PROBE_CLEAR));
    CHECK(virtual_inputs_get().mask == 2);
    CHECK(vi_command(NULL) == Status_OK);
    CHECK(strstr(output, "PROBE_SET=2,PROBE_CLR=1,TLS_SET=1,TLS_CLR=0"));
    CHECK(grbl.on_unknown_realtime_cmd((char)CMD_VINPUT_CLEAR_ALL));
    CHECK(virtual_inputs_get().mask == 0);
    CHECK(vi_command(NULL) == Status_OK);
    CHECK(strstr(output, "PROBE_SET=2,PROBE_CLR=2,TLS_SET=1,TLS_CLR=1"));
    return 0;
}
