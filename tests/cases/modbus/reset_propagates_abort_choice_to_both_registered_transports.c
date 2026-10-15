#include <string.h>
#include "grbl.h"
#include "modbus.h"
#include "check.h"
static unsigned rtu_calls, tcp_calls;
static bool rtu_abort, tcp_abort;
static void rtu_reset(bool abort) { rtu_calls++; rtu_abort = abort; }
static void tcp_reset(bool abort) { tcp_calls++; tcp_abort = abort; }
int main(void)
{
    modbus_api_t rtu = {.interface = Modbus_InterfaceRTU, .reset = rtu_reset};
    modbus_api_t tcp = {.interface = Modbus_InterfaceTCP, .reset = tcp_reset};
    CHECK(modbus_register_api(&rtu)); CHECK(modbus_register_api(&tcp));
    modbus_reset(false); CHECK(rtu_calls == 1 && tcp_calls == 1);
    CHECK(!rtu_abort && !tcp_abort);
    modbus_reset(true); CHECK(rtu_calls == 2 && tcp_calls == 2);
    CHECK(rtu_abort && tcp_abort);
    return EXIT_SUCCESS;
}
