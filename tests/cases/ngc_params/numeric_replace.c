#include "support/engine_host.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    float value; CHECK(ngc_param_set(100, 12.5f)); CHECK(ngc_param_set(100, -7.25f)); CHECK(ngc_param_get(100, &value)); NEAR(value, -7.25f);
    return EXIT_SUCCESS;
}
