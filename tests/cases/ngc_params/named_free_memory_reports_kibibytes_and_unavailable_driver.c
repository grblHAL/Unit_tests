#include "support/named_parameter_host.h"
#include "check.h"
static uint32_t memory_available(void) { return 2560; }
int main(void)
{
    engine_parser_prepare();
    hal.get_free_mem = NULL;
    NEAR(read_named_parameter("_free_memory"), -1);
    hal.get_free_mem = memory_available;
    NEAR(read_named_parameter("_free_memory"), 2.5f);
    return EXIT_SUCCESS;
}
