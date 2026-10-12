#include <string.h>
#include "grbl.h"
#include "modbus.h"
#include "check.h"

int main(void)
{
    const modbus_function_properties_t *p = modbus_get_function_properties(ModBus_ReadHoldingRegisters);
    CHECK(p != NULL); CHECK(!p->is_write); CHECK(!p->single_register); CHECK(!p->packed);
    p = modbus_get_function_properties(ModBus_WriteCoil); CHECK(p != NULL); CHECK(p->is_write); CHECK(p->single_register);
    CHECK(modbus_get_function_properties((modbus_function_t)0) == NULL); CHECK(modbus_get_function_properties((modbus_function_t)255) == NULL);
    return EXIT_SUCCESS;
}
