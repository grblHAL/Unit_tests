#include <string.h>
#include "grbl.h"
#include "modbus.h"
#include "check.h"
static unsigned calls;
static void flush(void) { calls++; }
int main(void)
{
    modbus_api_t api = {.interface = Modbus_InterfaceRTU, .flush_queue = flush};
    CHECK(modbus_register_api(&api)); api.interface = Modbus_InterfaceTCP; CHECK(modbus_register_api(&api));
    modbus_flush_queue(); CHECK(calls == 2);
    return EXIT_SUCCESS;
}
