#include "support/passthru_host.h"
#include "check.h"

int main(void)
{
    prepare_passthru();
    start_passthru();
    finish_passthru_startup();
    for(unsigned i = 0; i < 130; i++) uart_input[i] = (uint8_t)i;
    uart_input_length = 130;
    engine_ticks = 1258;
    engine_execute_tasks(STATE_IDLE);
    CHECK(usb_output_length == 130);
    CHECK(usb_chunks == 3);
    CHECK(memcmp(usb_output, uart_input, 130) == 0);
    return EXIT_SUCCESS;
}
