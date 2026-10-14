#include "support/nvs_debug_host.h"
#include "stream.h"
static unsigned drain_calls;
static uint16_t pending_output(void)
{
    CHECK(strstr(engine_output, "[MSG:Debug: axis=2 position=12.50]") != NULL);
    return ++drain_calls < 3 ? 1 : 0;
}
int main(void)
{
    prepare_nvs_debug(); hal.stream.get_tx_buffer_count = pending_output;
    debug_printf("axis=%u position=%.2f", 2u, 12.5);
    CHECK(drain_calls == 3);
    CHECK(strcmp(engine_output, "[MSG:Debug: axis=2 position=12.50]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
