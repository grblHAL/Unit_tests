#include "support/engine_host.h"
#include "ngc_expr.h"
#include "ngc_params.h"
#include "check.h"
#include <string.h>
int main(void)
{
    engine_parser_prepare();
    CHECK(ngc_param_set(1, 7.25f));
    char text[] = "%d#1 / %f#1";
    char *result = ngc_substitute_parameters(text);
    CHECK(result != NULL);
    CHECK(strcmp(result, "7 / 7.250") == 0);
    free(result);
    return EXIT_SUCCESS;
}
