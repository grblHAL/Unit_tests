#include "support/engine_host.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char name[] = "_metric"; float value; CHECK(ngc_named_param_get(name, &value)); CHECK(value == 1); CHECK(!ngc_named_param_set(name, 0));
    return EXIT_SUCCESS;
}
