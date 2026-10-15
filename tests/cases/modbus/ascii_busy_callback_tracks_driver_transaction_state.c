#include <string.h>
#include "grbl.h"
#include "modbus.h"
#include "check.h"
static bool busy;
static unsigned calls;
static bool is_busy(void) { calls++; return busy; }
int main(void)
{
    modbus_api_t api = {.interface = Modbus_InterfaceASCII, .is_busy = is_busy};
    CHECK(modbus_register_api(&api));
    CHECK(!modbus_isbusy()); busy = true; CHECK(modbus_isbusy());
    busy = false; CHECK(!modbus_isbusy()); CHECK(calls == 3);
    return EXIT_SUCCESS;
}
