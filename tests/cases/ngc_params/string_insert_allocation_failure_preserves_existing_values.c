#include "support/named_parameter_host.h"
#include "support/realloc_failure_host.h"

int main(void)
{
    engine_parser_prepare();
    char first[] = "first", second[] = "second";
    CHECK(ngc_string_param_set(1, first));
    fail_realloc = true;
    CHECK(!ngc_string_param_set(2, second));
    fail_realloc = false;
    CHECK(failed_realloc_calls == 1);
    CHECK(!ngc_string_param_exists(2));
    CHECK(strcmp(ngc_string_param_get(1), first) == 0);
    CHECK(ngc_string_param_set(2, second));
    CHECK(strcmp(ngc_string_param_get(2), second) == 0);
    ngc_string_param_delete(1); ngc_string_param_delete(2);
    return EXIT_SUCCESS;
}
