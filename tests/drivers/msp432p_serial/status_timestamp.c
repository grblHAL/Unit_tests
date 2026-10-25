#include "msp_host.h"
int main(void)
{
    msp_start();
    now = 1234;
    msp_receive(CMD_STATUS_REPORT_LEGACY);
    CHECK(stream_get_uart_status(0)->last_status_request == 1234 &&
          msp_stream->read() == SERIAL_NO_DATA);
    now = 2345;
    msp_receive(CMD_STATUS_REPORT);
    CHECK(stream_get_uart_status(0)->last_status_request == 2345);
    return 0;
}
