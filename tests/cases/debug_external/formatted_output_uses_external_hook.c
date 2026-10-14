#include "support/debug_external_host.h"
int main(void)
{
    engine_prepare();
    debug_printf("X=%d Y=%d",12,-7);
    CHECK(strcmp(external_output,"X=12 Y=-7" ASCII_EOL) == 0);
    CHECK(external_write_calls == 2);
    return 0;
}
