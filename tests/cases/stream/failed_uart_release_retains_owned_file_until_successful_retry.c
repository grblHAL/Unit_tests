#include "support/stream_file_close_host.h"
int main(void)
{
    prepare_file_uart();
    file_uart_release_fails = true;
    CHECK(!stream_close(&file_uart_device));
    CHECK(owned_uart_file_closes == 0 && uart_property.flags.claimed);
    CHECK(file_uart_device.file == &owned_uart_file);
    file_uart_release_fails = false;
    CHECK(stream_close(&file_uart_device));
    CHECK(owned_uart_file_closes == 1 && release_calls == 2);
    CHECK(!uart_property.flags.claimed);
    return EXIT_SUCCESS;
}
