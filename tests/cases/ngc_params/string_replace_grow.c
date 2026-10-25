#include "support/engine_host.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char initial[] = "a", expanded[] = "longer parameter value", short_value[] = "job";
    CHECK(ngc_string_param_set(100, initial));
    CHECK(ngc_string_param_set(100, expanded));
    CHECK(strcmp(ngc_string_param_get(100), expanded) == 0);
    CHECK(ngc_string_param_set(100, short_value));
    CHECK(strcmp(ngc_string_param_get(100), short_value) == 0);
    CHECK(strlen(ngc_string_param_get(100)) == 3);
    ngc_string_param_delete(100);
    CHECK(!ngc_string_param_exists(100));
    /* Repeated cleanup after the last entry is removed must permit reuse. */
    ngc_string_param_delete(100);
    CHECK(ngc_string_param_set(100, initial));
    CHECK(strcmp(ngc_string_param_get(100), initial) == 0);
    ngc_string_param_delete(100);
    return EXIT_SUCCESS;
}
