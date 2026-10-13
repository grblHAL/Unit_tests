#include "support/named_parameter_host.h"

int main(void)
{
    engine_parser_prepare();
    char value[256]; memset(value, 'x', 255); value[255] = 0;
    CHECK(ngc_string_param_set(1, value));
    CHECK(strlen(ngc_string_param_get(1)) == 255);
    CHECK(strcmp(ngc_string_param_get(1), value) == 0);
    ngc_string_param_delete(1);
    return EXIT_SUCCESS;
}
