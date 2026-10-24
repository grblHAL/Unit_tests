#include "vinput_host.h"
int main(void)
{
    vi_start(true);
    CHECK(grbl.on_unknown_realtime_cmd((char)CMD_VINPUT_PROBE_SET));
    CHECK(vi_command("RST") == Status_OK);
    CHECK(virtual_input_get(VInput_Probe));
    CHECK(strstr(output, "PROBE_SET=0,PROBE_CLR=0,TLS_SET=0,TLS_CLR=0"));
    CHECK(grbl.on_unknown_realtime_cmd((char)CMD_VINPUT_TLS_CLEAR));
    CHECK(vi_command("rst") == Status_OK);
    CHECK(strstr(output, "TLS_CLR=0"));
    return 0;
}
