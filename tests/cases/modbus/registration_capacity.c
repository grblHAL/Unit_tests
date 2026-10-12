#include <string.h>
#include "grbl.h"
#include "modbus.h"
#include "check.h"

int main(void)
{
    modbus_api_t api = {.interface = Modbus_InterfaceRTU};
    CHECK(modbus_register_api(&api)); CHECK(modbus_enabled());
    api.interface = Modbus_InterfaceTCP; CHECK(modbus_register_api(&api)); CHECK(!modbus_register_api(&api));
    return EXIT_SUCCESS;
}
