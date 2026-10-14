#include "support/debug_serial_host.h"
int main(void)
{
    start_debug_serial();
    debug_write("WorkBee");
    CHECK(strcmp(debug_output,"WorkBee") == 0);
    CHECK(debug_drain_calls == 1);
    CHECK(engine_output[0] == 0);
    return 0;
}
