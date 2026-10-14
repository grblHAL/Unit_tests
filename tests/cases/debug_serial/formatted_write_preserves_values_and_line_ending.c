#include "support/debug_serial_host.h"
int main(void)
{
    start_debug_serial();
    debug_printf("axis %c steps %u",'X',42u);
    CHECK(strcmp(debug_output,"axis X steps 42" ASCII_EOL) == 0);
    CHECK(debug_drain_calls == 1);
    return 0;
}
