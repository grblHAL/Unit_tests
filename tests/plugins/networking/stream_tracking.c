#include "net_host.h"
int main(void)
{
    net_prepare();
    net_add(0, (network_status_t){.flags.interface_up = On});
    hal.stream.type = StreamType_Telnet;
    grbl.on_stream_changed();
    grbl.on_report_options(false);
    CHECK(strstr(net_output, "[NETCON:Telnet]"));
    net_clear();
    net_file = true;
    hal.stream.type = StreamType_Serial;
    grbl.on_stream_changed();
    grbl.on_report_options(false);
    CHECK(strstr(net_output, "[NETCON:Telnet]"));
    net_file = false;
    hal.stream.type = StreamType_WebSocket;
    grbl.on_stream_changed();
    net_clear();
    grbl.on_report_options(false);
    CHECK(strstr(net_output, "[NETCON:Websocket]") && net_previous_streams == 3);
    return 0;
}
