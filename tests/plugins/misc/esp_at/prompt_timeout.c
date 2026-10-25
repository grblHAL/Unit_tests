#include "at_host.h"
int main(void)
{
    at_prepare();
    at_prompt = false;
    at_load(WiFiMode_AP);
    at_start();
    at_connect();
    CHECK(at_pending() == 1);
    for (unsigned i = 0; i < 9; i++)
        at_step(2);
    CHECK(hal.stream.type == StreamType_Serial && hal.stream.instance == 0 && at_pending() == 1);
    CHECK(at_command_seen("AT+CWQIF\n"));
    at_prompt = true;
    at_connect();
    CHECK(hal.stream.read() == ASCII_CAN && !at_pending());
    return 0;
}
