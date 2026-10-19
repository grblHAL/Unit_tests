#include "support/stream_file_close_host.h"
int main(void)
{
    prepare_file_uart();
    CHECK(owned_uart_file_closes == 0);
    CHECK(stream_close(&file_uart_device));
    CHECK(owned_uart_file_closes == 1 && release_calls == 1);
    CHECK(receive_disabled && !uart_property.flags.claimed);
    return EXIT_SUCCESS;
}
