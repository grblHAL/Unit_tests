#include <string.h>
#include "grbl.h"
#include "modbus.h"
#include "check.h"

int main(void)
{
    CHECK(!modbus_enabled()); CHECK(!modbus_isbusy()); CHECK(modbus_isup().ok == 0);
    modbus_message_t msg = {0}; CHECK(!modbus_send(&msg, NULL, false));
    modbus_flush_queue(); modbus_set_silence(NULL);
    return EXIT_SUCCESS;
}
