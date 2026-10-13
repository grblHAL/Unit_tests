#include "support/named_parameter_host.h"
#include "support/realloc_failure_host.h"

int main(void)
{
    engine_parser_prepare();
    char name[] = "fixture name";
    fail_realloc = true;
    CHECK(ngc_string_param_set_name(name) == 0);
    fail_realloc = false;
    CHECK(failed_realloc_calls == 1);
    ngc_string_id_t id = ngc_string_param_set_name(name);
    CHECK(id > NGC_MAX_PARAM_ID);
    CHECK(strcmp(ngc_string_param_get(id), name) == 0);
    CHECK(ngc_string_param_set_name(name) == id);
    ngc_string_param_delete(id);
    return EXIT_SUCCESS;
}
