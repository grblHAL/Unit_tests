#include "support/debug_serial_host.h"
int main(void)
{
    start_debug_serial();
    debug_reenter = true;
    debug_writeln("outer");
    CHECK(strcmp(debug_output,"outer" ASCII_EOL) == 0);
    CHECK(debug_drain_calls == 1);
    debug_writeln("next");
    CHECK(strcmp(debug_output,"outer" ASCII_EOL "next" ASCII_EOL) == 0);
    return 0;
}
