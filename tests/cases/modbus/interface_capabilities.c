#include <string.h>
#include "grbl.h"
#include "modbus.h"
#include "check.h"
static bool up(void) { return true; }
int main(void)
{
    modbus_api_t api = {.interface = Modbus_InterfaceRTU, .is_up = up};
    CHECK(modbus_register_api(&api)); CHECK(modbus_isup().rtu); CHECK(!modbus_isup().tcp);
    api.interface = Modbus_InterfaceTCP; CHECK(modbus_register_api(&api));
    CHECK(modbus_isup().rtu); CHECK(modbus_isup().tcp);
    return EXIT_SUCCESS;
}
