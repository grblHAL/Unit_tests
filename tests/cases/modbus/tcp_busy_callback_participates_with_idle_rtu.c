#include <string.h>
#include "grbl.h"
#include "modbus.h"
#include "check.h"
static unsigned tcp_calls, rtu_calls;
static bool tcp_busy(void) { tcp_calls++; return true; }
static bool rtu_busy(void) { rtu_calls++; return false; }
int main(void)
{
    modbus_api_t tcp = {.interface = Modbus_InterfaceTCP, .is_busy = tcp_busy};
    modbus_api_t rtu = {.interface = Modbus_InterfaceRTU, .is_busy = rtu_busy};
    CHECK(modbus_register_api(&tcp)); CHECK(modbus_register_api(&rtu));
    CHECK(modbus_isbusy()); CHECK(tcp_calls == 1 && rtu_calls == 1);
    return EXIT_SUCCESS;
}
