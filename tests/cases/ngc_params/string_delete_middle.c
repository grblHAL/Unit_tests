#include "support/engine_host.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char value[] = "value";
    CHECK(ngc_string_param_set(1, value));
    CHECK(ngc_string_param_set(2, value));
    CHECK(ngc_string_param_set(3, value));
    ngc_string_param_delete(999);
    for(unsigned id = 1; id <= 3; id++)
        CHECK(strcmp(ngc_string_param_get(id), value) == 0);
    ngc_string_param_delete(2);
    CHECK(ngc_string_param_exists(1));
    CHECK(!ngc_string_param_exists(2));
    CHECK(ngc_string_param_exists(3));
    ngc_string_param_delete(2);
    CHECK(strcmp(ngc_string_param_get(1), value) == 0);
    CHECK(strcmp(ngc_string_param_get(3), value) == 0);
    ngc_string_param_delete(1);
    ngc_string_param_delete(3);
    return EXIT_SUCCESS;
}
