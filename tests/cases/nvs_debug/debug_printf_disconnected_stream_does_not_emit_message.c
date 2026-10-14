#include "support/nvs_debug_host.h"
#include "stream.h"
int main(void)
{
    prepare_nvs_debug(); debug_connected = false;
    debug_printf("axis=%u", 2u);
    CHECK(engine_output[0] == 0);
    return EXIT_SUCCESS;
}
