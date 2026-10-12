#include "support/passthru_host.h"
#include "check.h"

int main(void)
{
    prepare_passthru();
    output_pins[0].function = Output_Aux0;
    stream_passthru_init(1, 115200, true);
    CHECK(!hal.stream.state.passthru);
    CHECK(usb_handler == NULL);
    return EXIT_SUCCESS;
}
