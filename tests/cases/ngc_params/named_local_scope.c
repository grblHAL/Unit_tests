#include "support/engine_host.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char name[] = "local";
    float value;
    int context;
    CHECK(ngc_named_param_set(name, 4));
    CHECK(ngc_call_push(&context));
    CHECK(!ngc_named_param_get(name, &value));
    CHECK(ngc_named_param_set(name, 9));
    CHECK(ngc_named_param_get(name, &value));
    CHECK(value == 9);
    (void)ngc_call_pop();
    CHECK(ngc_named_param_get(name, &value));
    CHECK(value == 4);
    return EXIT_SUCCESS;
}
