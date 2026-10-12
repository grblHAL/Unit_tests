#include "support/report_host.h"
#include "stream.h"
#include "check.h"

int main(void)
{
    prepare_report();
    CHECK(report_uart_ports(STATE_IDLE, NULL) == Status_OK);
    CHECK(engine_output[0] == '\0');
    return EXIT_SUCCESS;
}
