#include "support/uart_report_host.h"
#include "check.h"

int main(void)
{
    prepare_uart_report();
    hal.enumerate_pins = enumerate_uart_pins;
    uart_pin_count = 1;
    CHECK(report_uart_ports(STATE_IDLE, NULL) == Status_OK);
    CHECK(strcmp(engine_output, "[PORT:1|Pendant|PA9,TX|]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
