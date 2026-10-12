#include "support/engine_host.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    float value = 9; CHECK(!ngc_param_set(0, 1)); CHECK(!ngc_param_get(0, &value)); CHECK(value == 0); CHECK(!ngc_param_get(65535, &value)); CHECK(!ngc_param_exists(65535));
    return EXIT_SUCCESS;
}
