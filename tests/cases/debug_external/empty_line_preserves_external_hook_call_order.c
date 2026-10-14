#include "support/debug_external_host.h"
int main(void)
{
    engine_prepare();
    debug_writeln("");
    CHECK(strcmp(external_output, ASCII_EOL) == 0);
    CHECK(external_write_calls == 2);
    return EXIT_SUCCESS;
}
