#include "support/engine_host.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char name[] = "";
    CHECK(ngc_string_param_set_name(name) == 0);
    return EXIT_SUCCESS;
}
