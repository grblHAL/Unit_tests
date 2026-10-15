#include <string.h>
#include "grbl.h"
#include "modbus.h"
#include "check.h"
static bool available;
static bool up(void) { return available; }
int main(void)
{
    modbus_api_t api = {.interface = Modbus_InterfaceASCII, .is_up = up};
    CHECK(modbus_register_api(&api));
    CHECK(modbus_enabled()); CHECK(modbus_isup().ok == 0);
    available = true;
    CHECK(modbus_isup().ascii); CHECK(!modbus_isup().rtu && !modbus_isup().tcp);
    available = false; CHECK(modbus_isup().ok == 0);
    return EXIT_SUCCESS;
}
