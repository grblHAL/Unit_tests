#include "support/engine_host.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char name[] = "parameter name"; ngc_string_id_t id = ngc_string_param_set_name(name); CHECK(id > NGC_MAX_PARAM_ID); CHECK(ngc_string_param_set_name(name) == id); CHECK(strcmp(ngc_string_param_get(id), name) == 0); ngc_string_param_delete(id);
    return EXIT_SUCCESS;
}
