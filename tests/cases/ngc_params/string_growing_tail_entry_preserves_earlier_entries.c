#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();
    char first[] = "first", second[] = "second", third[] = "third";
    CHECK(ngc_string_param_set(1, first));
    CHECK(ngc_string_param_set(2, second));
    CHECK(ngc_string_param_set(3, third));
    char expanded[241];
    memset(expanded, 'x', 240); expanded[240] = '\0';
    CHECK(ngc_string_param_set(3, expanded));
    CHECK(strcmp(ngc_string_param_get(3), expanded) == 0);
    CHECK(strcmp(ngc_string_param_get(1), first) == 0);
    CHECK(strcmp(ngc_string_param_get(2), second) == 0);
    for(unsigned id = 1; id <= 3; id++) ngc_string_param_delete(id);
    CHECK(!ngc_string_param_exists(1) && !ngc_string_param_exists(2) && !ngc_string_param_exists(3));
    return EXIT_SUCCESS;
}
