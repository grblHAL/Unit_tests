#include <string.h>
#include "grbl.h"
#include "modbus.h"
#include "check.h"
static bool idle(void) { return false; }
static bool busy(void) { return true; }
int main(void)
{
    modbus_api_t api = {.interface = Modbus_InterfaceRTU, .is_busy = idle}; CHECK(modbus_register_api(&api));
    CHECK(!modbus_isbusy()); api.interface = Modbus_InterfaceTCP; api.is_busy = busy;
    CHECK(modbus_register_api(&api)); CHECK(modbus_isbusy());
    return EXIT_SUCCESS;
}
