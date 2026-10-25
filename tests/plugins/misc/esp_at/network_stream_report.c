#include "at_host.h"
int main(void)
{
    at_prepare();
    at_load(WiFiMode_AP);
    at_start();
    at_connect();
    CHECK(hal.stream.read() == ASCII_CAN);
    at_output[0] = 0;
    grbl.on_report_options(false);
    CHECK(at_tx_length < sizeof(at_tx));
    at_tx[at_tx_length] = 0;
    CHECK(strstr(at_tx, "[NETCON:Telnet]") && !strstr(at_output, "[NETCON:Telnet]"));
    return 0;
}
