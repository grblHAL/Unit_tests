#include "support/engine_host.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char value[] = "value"; CHECK(ngc_string_param_set(1, value)); CHECK(ngc_string_param_set(2, value)); CHECK(ngc_string_param_set(3, value)); ngc_string_param_delete(2); CHECK(ngc_string_param_exists(1)); CHECK(!ngc_string_param_exists(2)); CHECK(ngc_string_param_exists(3)); ngc_string_param_delete(1); ngc_string_param_delete(3);
    return EXIT_SUCCESS;
}
