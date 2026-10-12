#include <string.h>
#include "grbl.h"
#include "modbus.h"
#include "check.h"
static unsigned tcp_calls, rtu_calls;
static bool send_tcp(modbus_message_t *msg, const modbus_callbacks_t *cb, bool block) { (void)msg; (void)cb; CHECK(block); tcp_calls++; return true; }
static bool send_rtu(modbus_message_t *msg, const modbus_callbacks_t *cb, bool block) { (void)msg; (void)cb; (void)block; rtu_calls++; return true; }
int main(void)
{
    modbus_api_t rtu = {.interface = Modbus_InterfaceRTU, .send = send_rtu};
    modbus_api_t tcp = {.interface = Modbus_InterfaceTCP, .send = send_tcp};
    CHECK(modbus_register_api(&rtu)); CHECK(modbus_register_api(&tcp));
    modbus_message_t msg = {0}; CHECK(modbus_send(&msg, NULL, true)); CHECK(tcp_calls == 1); CHECK(rtu_calls == 0);
    return EXIT_SUCCESS;
}
