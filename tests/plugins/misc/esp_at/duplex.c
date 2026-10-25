#include "at_host.h"
int main(void)
{
    at_prepare();
    at_load(WiFiMode_AP);
    at_start();
    at_connect();
    CHECK(hal.stream.read() == ASCII_CAN && hal.stream.read() == SERIAL_NO_DATA);
    const char input[] = "G1X1\nC1\nW10\n";
    for (unsigned i = 0; i < sizeof(input) - 1; i++)
        CHECK(at_uart_handler(input[i]));
    for (unsigned i = 0; i < sizeof(input) - 1; i++)
        CHECK(hal.stream.read() == input[i]);
    CHECK(hal.stream.read() == SERIAL_NO_DATA && !at_pending());
    const uint8_t binary[] = {0, 42, 0xff, '\n'};
    hal.stream.write_n(binary, sizeof(binary));
    hal.stream.write("ok\r\n");
    CHECK(at_tx_length == sizeof(binary) + 4 && !memcmp(at_tx, binary, sizeof(binary)));
    CHECK(!memcmp(at_tx + sizeof(binary), "ok\r\n", 4));
    return 0;
}
