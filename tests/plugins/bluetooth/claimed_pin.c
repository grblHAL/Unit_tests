#include "bt_host.h"
int main(void)
{
    bt_prepare(2, true);
    bluetooth_init();
    bt_settings->restore();
    CHECK(bt_port(0) == Status_OK);
    bt_enable(true);
    bt_settings->save();
    uint8_t port = 0;
    CHECK(ioport_claim(Port_Digital, Port_Input, &port, "Other plugin"));
    bt_settings->load();
    bt_run();
    CHECK(bt_warnings == 1 && strstr(bt_output, "no pin for STATE") && !bt_commands &&
          hal.stream.type == StreamType_Serial);
    return 0;
}
