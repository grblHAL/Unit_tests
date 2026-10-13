#include "support/named_parameter_host.h"
#include "support/realloc_failure_host.h"

int main(void)
{
    engine_parser_prepare();
    char first[] = "first", middle[] = "middle", last[] = "last";
    CHECK(ngc_string_param_set(1, first));
    CHECK(ngc_string_param_set(2, middle));
    CHECK(ngc_string_param_set(3, last));
    char expanded[241]; memset(expanded, 'x', 240); expanded[240] = 0;
    fail_realloc = true;
    CHECK(!ngc_string_param_set(2, expanded));
    fail_realloc = false;
    CHECK(failed_realloc_calls == 1);
    CHECK(strcmp(ngc_string_param_get(1), first) == 0);
    CHECK(strcmp(ngc_string_param_get(3), last) == 0);
    CHECK(ngc_string_param_set(2, expanded));
    CHECK(strcmp(ngc_string_param_get(2), expanded) == 0);
    for(unsigned id = 1; id <= 3; id++) ngc_string_param_delete(id);
    return EXIT_SUCCESS;
}
