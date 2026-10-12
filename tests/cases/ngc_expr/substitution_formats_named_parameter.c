#include "support/engine_host.h"
#include "ngc_expr.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char name[] = "part";
    CHECK(ngc_named_param_set(name, 7.5f));
    char text[] = "part=#<part>";
    char *result = ngc_substitute_parameters(text);
    CHECK(result != NULL);
    CHECK(strcmp(result, "part=7.500") == 0);
    free(result);
    return EXIT_SUCCESS;
}
