#include "support/uart_report_host.h"
int main(void)
{
    uart_status_available = false;
    prepare_uart_report();
    uart_pins[0].port = uart_pins[1].port = NULL;
    hal.enumerate_pins = enumerate_uart_pins;
    hal.stream.write_char = report_character;
    port_status.baud_rate = 230400;
    CHECK(report_uart_ports(STATE_IDLE, NULL) == Status_OK);
    CHECK(strcmp(engine_output, "[PORT:1|Pendant|9,TX|10,RX]" ASCII_EOL) == 0);
    engine_output[0] = '\0';
    uart_status_available = true;
    CHECK(report_uart_ports(STATE_IDLE, NULL) == Status_OK);
    CHECK(strcmp(engine_output, "[PORT:1|Pendant|9,TX|10,RX|230400,8,N,1|F]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
