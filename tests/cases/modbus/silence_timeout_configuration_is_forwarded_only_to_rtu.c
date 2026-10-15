#include <string.h>
#include "grbl.h"
#include "modbus.h"
#include "check.h"
static unsigned calls;
static const modbus_silence_timeout_t *received;
static void silence(const modbus_silence_timeout_t *timeout) { calls++; received = timeout; }
int main(void)
{
    modbus_silence_timeout_t timeout = {.b2400 = 20, .b115200 = 2};
    modbus_set_silence(&timeout); CHECK(calls == 0);
    modbus_api_t api = {.interface = Modbus_InterfaceRTU, .set_silence = silence};
    CHECK(modbus_register_api(&api));
    modbus_set_silence(&timeout); CHECK(calls == 1 && received == &timeout);
    CHECK(received->b2400 == 20 && received->b115200 == 2);
    return EXIT_SUCCESS;
}
