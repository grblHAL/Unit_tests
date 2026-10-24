#include "bt_host.h"
int main(void)
{
    bt_prepare(2, true);
    bt_load();
    CHECK(bt_enabled() == 1 && bt_commands == 4 && !bt_warnings);
    CHECK(
        !strcmp(bt_command_log, "AT\r\nAT+UART=115200,1,0\r\nAT+NAME=grblHAL\r\nAT+POLAR=1,1\r\n"));
    CHECK(bt_bauds == 2 && bt_baud[0] == 38400 && bt_baud[1] == 115200);
    CHECK(hal.stream.type == StreamType_Serial &&
          bt_base_handler == protocol_enqueue_realtime_command && strstr(bt_output, "successful"));
    return 0;
}
