#include "support/debug_serial_host.h"
int main(void)
{
    prepare_debug_serial();
    debug_write("raw");
    debug_writeln("line");
    debug_printf("%u",42u);
    CHECK(debug_output[0] == 0);
    CHECK(debug_drain_calls == 0);
    return 0;
}
