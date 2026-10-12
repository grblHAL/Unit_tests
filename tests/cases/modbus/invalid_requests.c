#include <string.h>
#include "grbl.h"
#include "modbus.h"
#include "check.h"

int main(void)
{
    uint16_t value = 0;
    CHECK(modbus_message(1, ModBus_ReadHoldingRegisters, 0, &value, 0, NULL) == Status_InvalidStatement);
    CHECK(modbus_message(1, (modbus_function_t)255, 0, &value, 1, NULL) == Status_InvalidStatement);
    CHECK(modbus_message(1, ModBus_ReadHoldingRegisters, 0, &value, MODBUS_MAX_REGISTERS + 1, NULL) == Status_InvalidStatement);
    return EXIT_SUCCESS;
}
