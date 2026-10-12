#include "support/engine_host.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    int context;
    float value;
    char name[] = "local";
    CHECK(ngc_call_push(&context));
    CHECK(ngc_param_set(1, 7));
    CHECK(ngc_named_param_set(name, 8));
    (void)ngc_call_pop();
    CHECK(ngc_call_push(&context));
    CHECK(ngc_param_get(1, &value));
    CHECK(value == 0);
    CHECK(!ngc_named_param_exists(name));
    (void)ngc_call_pop();
    return EXIT_SUCCESS;
}
