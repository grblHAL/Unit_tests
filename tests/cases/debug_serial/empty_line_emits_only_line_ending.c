#include "support/debug_serial_host.h"
int main(void)
{
    start_debug_serial();
    debug_writeln("");
    CHECK(strcmp(debug_output, ASCII_EOL) == 0);
    CHECK(debug_drain_calls == 1);
    return EXIT_SUCCESS;
}
