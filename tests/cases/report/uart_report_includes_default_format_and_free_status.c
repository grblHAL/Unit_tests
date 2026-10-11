#include "support/uart_report_host.h"
#include "check.h"

int main(void)
{
    prepare_uart_report();
    hal.stream.write_char = report_character;
    port_status.baud_rate = 115200;
    CHECK(report_uart_ports(STATE_IDLE, NULL) == Status_OK);
    CHECK(strcmp(engine_output, "[PORT:1|UART|||115200,8,N,1|F]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
