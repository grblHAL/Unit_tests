#include "support/engine_host.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char a[] = "a", b[] = "longer parameter value"; CHECK(ngc_string_param_set(100, a)); CHECK(ngc_string_param_set(100, b)); CHECK(strcmp(ngc_string_param_get(100), b) == 0); ngc_string_param_delete(100); CHECK(!ngc_string_param_exists(100));
    return EXIT_SUCCESS;
}
