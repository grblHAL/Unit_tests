#include "support/passthru_host.h"
#include "check.h"

int main(void)
{
    prepare_passthru();
    start_passthru();
    CHECK(usb_handler != NULL);
    CHECK(usb_handler(0));
    CHECK(usb_handler(0xff));
    CHECK(usb_handler('!'));
    CHECK(uart_output_length == 3);
    CHECK(uart_output[0] == 0 && uart_output[1] == 0xff && uart_output[2] == '!');
    return EXIT_SUCCESS;
}
