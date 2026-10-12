#include <string.h>
#include "grbl.h"
#include "modbus.h"
#include "check.h"
static unsigned calls;
static bool send_request(modbus_message_t *msg, const modbus_callbacks_t *cb, bool block) {
    calls++; CHECK(block); CHECK(cb != NULL); CHECK(msg->crc_check);
    const uint8_t expected[] = {7, 3, 0x12, 0x34, 0, 2};
    CHECK(memcmp(msg->adu, expected, sizeof(expected)) == 0);
    CHECK(msg->tx_length == 8); CHECK(msg->rx_length == 9); return true;
}
int main(void)
{
    modbus_api_t api = {.interface = Modbus_InterfaceRTU, .send = send_request}; CHECK(modbus_register_api(&api));
    uint16_t values[2] = {0}; CHECK(modbus_message(7, ModBus_ReadHoldingRegisters, 0x1234, values, 2, NULL) == Status_OK);
    CHECK(calls == 1);
    return EXIT_SUCCESS;
}
