#include "support/named_parameter_host.h"

int main(void)
{
    engine_parser_prepare();
    char previous[] = "previous";
    CHECK(ngc_string_param_set(1, previous));
    char value[257]; memset(value, 'x', 256); value[256] = 0;
    CHECK(!ngc_string_param_set(1, value));
    char replacement[] = "retry";
    CHECK(ngc_string_param_set(1, replacement));
    char *stored = ngc_string_param_get(1);
    CHECK(stored != NULL);
    CHECK(strcmp(stored, replacement) == 0);
    ngc_string_param_delete(1);
    return EXIT_SUCCESS;
}
