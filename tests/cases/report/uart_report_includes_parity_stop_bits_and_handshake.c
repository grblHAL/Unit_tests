#include "support/uart_report_host.h"
#include "check.h"

int main(void)
{
    prepare_uart_report();
    hal.stream.write_char = report_character;
    port_status.baud_rate = 9600;
    port_status.format.width = 1;
    port_status.format.parity = Serial_ParityEven;
    port_status.format.stopbits = 2;
    port_status.flags.claimed = true;
    port_status.flags.rts_handshake = true;
    CHECK(report_uart_ports(STATE_IDLE, NULL) == Status_OK);
    CHECK(strcmp(engine_output, "[PORT:1|UART|||9600,7,E,2,P|C]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
