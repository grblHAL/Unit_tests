#include "support/engine_host.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    float value = -1; CHECK(ngc_param_get(100, &value)); CHECK(value == 0);
    return EXIT_SUCCESS;
}
