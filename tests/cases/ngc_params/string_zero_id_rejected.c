#include "support/engine_host.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char value[] = "test";
    CHECK(!ngc_string_param_set(0, value));
    CHECK(!ngc_string_param_exists(0));
    return EXIT_SUCCESS;
}
