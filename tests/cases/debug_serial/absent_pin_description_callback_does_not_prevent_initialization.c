#include "support/debug_serial_host.h"
int main(void)
{
    prepare_debug_serial();
    hal.periph_port.set_pin_description = NULL;
    CHECK(debug_stream_init());
    CHECK(debug_description_calls == 0);
    CHECK(debug_claim_calls == 1);
    return 0;
}
