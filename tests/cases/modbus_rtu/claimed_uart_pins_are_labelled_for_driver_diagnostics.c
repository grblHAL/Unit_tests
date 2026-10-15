#include "support/rtu_host.h"

static unsigned uart_labels;
static void label_uart(const pin_function_t function, const pin_group_t group, const char *description)
{
    CHECK(group == PinGroup_UART);
    CHECK(strcmp(description, "Modbus") == 0);
    if(function == Output_TX) uart_labels |= 1;
    else if(function == Input_RX) uart_labels |= 2;
    else CHECK(false);
}
static void install_uart_labels(void) { hal.periph_port.set_pin_description = label_uart; }
int main(void)
{
    prepare_rtu_transport(NULL, -2, install_uart_labels);
    CHECK(uart_labels == 3);
    send_request();
    inject_reply(false);
    poll_rtu();
    CHECK(rx_calls == 1 && exceptions == 0);
    return EXIT_SUCCESS;
}
