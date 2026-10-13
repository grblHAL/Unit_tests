#include "support/named_parameter_host.h"

int main(void)
{
    engine_parser_prepare();
    char value[257]; memset(value, 'x', 256); value[256] = 0;
    CHECK(!ngc_string_param_set(1, value));
    CHECK(!ngc_string_param_exists(1));
    return EXIT_SUCCESS;
}
