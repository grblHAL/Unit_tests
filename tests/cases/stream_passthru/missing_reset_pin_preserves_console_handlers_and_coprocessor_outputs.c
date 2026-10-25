#include "support/passthru_host.h"
int main(void)
{
    output_pins[1].function = Output_Aux1;
    prepare_passthru();
    stream_passthru_init(1, 115200, true);
    CHECK(!hal.stream.state.passthru);
    CHECK(usb_handler == NULL && uart_handler == NULL);
    CHECK(!pin_values[0] && !pin_values[1]);
    CHECK(cancelled == 0 && uart_output_length == 0 && usb_output_length == 0);
    sys.driver_started = true;
    task_execute_on_startup();
    CHECK(usb_handler == NULL && uart_handler == NULL);
    CHECK(!pin_values[0] && !pin_values[1] && cancelled == 0);
    return EXIT_SUCCESS;
}
