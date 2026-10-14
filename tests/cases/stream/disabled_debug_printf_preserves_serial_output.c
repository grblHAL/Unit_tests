#include "support/engine_host.h"
#include "stream.h"
#include "check.h"
int main(void)
{
    engine_prepare(); CHECK(DEBUG_PRINT == 0);
    debug_printf("diagnostic %u", 42u);
    CHECK(engine_output[0] == 0);
    return EXIT_SUCCESS;
}
