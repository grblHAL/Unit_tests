#include "support/engine_host.h"
#include "stream.h"
#include "check.h"
#include <string.h>
int main(void)
{
    engine_prepare();
    strcpy(engine_output, "primary output");
    CHECK(debug_stream_init());
    debug_write("raw"); debug_writeln("line"); debug_printf("steps=%u", 42u);
    CHECK(strcmp(engine_output, "primary output") == 0);
    return EXIT_SUCCESS;
}
