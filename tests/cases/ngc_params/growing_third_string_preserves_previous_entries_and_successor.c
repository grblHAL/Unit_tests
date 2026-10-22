#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();
    char initial[] = "small";
    for(unsigned id = 1; id <= 4; id++)
        CHECK(ngc_string_param_set(id, initial));
    char expanded[241];
    memset(expanded, 'x', 240);
    expanded[240] = 0;
    CHECK(ngc_string_param_set(3, expanded));
    for(unsigned id = 1; id <= 4; id++)
        CHECK(strcmp(ngc_string_param_get(id), id == 3 ? expanded : initial) == 0);
    ngc_string_param_delete(3);
    CHECK(!ngc_string_param_exists(3));
    CHECK(strcmp(ngc_string_param_get(4), initial) == 0);
    CHECK(ngc_string_param_set(3, initial));
    for(unsigned id = 1; id <= 4; id++) {
        CHECK(strcmp(ngc_string_param_get(id), initial) == 0);
        ngc_string_param_delete(id);
    }
    return EXIT_SUCCESS;
}
