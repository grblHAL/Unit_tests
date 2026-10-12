#include "support/engine_host.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(!ngc_param_set(5061, 8)); CHECK(!ngc_param_is_rw(5061)); CHECK(ngc_param_is_rw(5060));
    return EXIT_SUCCESS;
}
