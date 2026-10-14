#include "support/debug_serial_host.h"
int main(void)
{
    prepare_debug_serial();
    CHECK(debug_stream_init());
    CHECK(debug_claim_calls == 1);
    CHECK(debug_baud == 115200);
    CHECK(debug_property.flags.claimed);
    CHECK(debug_description_calls == 1);
    CHECK(strcmp(debug_output, ASCII_EOL "UART debug active:" ASCII_EOL) == 0);
    CHECK(debug_drain_calls == 1);
    CHECK(engine_output[0] == 0);
    return 0;
}
