#include "support/debug_external_host.h"
int main(void)
{
    engine_prepare();
    debug_writeln("probe triggered");
    CHECK(strcmp(external_output,"probe triggered" ASCII_EOL) == 0);
    CHECK(external_write_calls == 2);
    CHECK(engine_output[0] == 0);
    return 0;
}
