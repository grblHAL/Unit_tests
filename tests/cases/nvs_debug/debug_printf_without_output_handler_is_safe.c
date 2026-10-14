#include "support/nvs_debug_host.h"
#include "stream.h"
static unsigned drain_calls;
static uint16_t pending_output(void) { drain_calls++; return 0; }
int main(void)
{
    prepare_nvs_debug(); hal.stream.write = NULL;
    hal.stream.get_tx_buffer_count = pending_output;
    debug_printf("axis=%u", 2u);
    CHECK(engine_output[0] == 0 && drain_calls == 0);
    return EXIT_SUCCESS;
}
