#include "support/engine_host.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char empty[] = ""; char underscore[] = "_"; CHECK(!ngc_named_param_set(empty, 1)); CHECK(!ngc_named_param_set(underscore, 1)); CHECK(!ngc_named_param_exists(empty));
    return EXIT_SUCCESS;
}
