#include "support/rtu_host.h"
#include "check.h"

int main(void)
{
    prepare_rtu();
    modbus_message_t message = {.tx_length = MODBUS_MAX_ADU_SIZE + 1, .rx_length = 7};
    modbus_callbacks_t callbacks = {.on_rx_exception = failed};
    CHECK(!modbus_send(&message, &callbacks, false));
    CHECK(exceptions == 1 && exception_code == ModBus_IllegalSize);
    CHECK(tx_calls == 0);
    return EXIT_SUCCESS;
}
