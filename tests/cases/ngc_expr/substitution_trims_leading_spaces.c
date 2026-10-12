#include "support/engine_host.h"
#include "ngc_expr.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();

    char text[] = "   ready";
    char *result = ngc_substitute_parameters(text);
    CHECK(result != NULL);
    CHECK(strcmp(result, "ready") == 0);
    free(result);
    return EXIT_SUCCESS;
}
