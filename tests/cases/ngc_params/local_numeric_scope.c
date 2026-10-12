#include "support/engine_host.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    int context; float value; CHECK(ngc_param_set(1, 4)); CHECK(ngc_call_push(&context)); CHECK(ngc_param_get(1, &value)); CHECK(value == 0); CHECK(ngc_param_set(1, 9)); (void)ngc_call_pop(); CHECK(ngc_call_level() == 0); CHECK(ngc_param_get(1, &value)); CHECK(value == 4);
    return EXIT_SUCCESS;
}
