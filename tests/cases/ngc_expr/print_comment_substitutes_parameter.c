#include "support/engine_host.h"
#include "ngc_expr.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(ngc_param_set(1, 7.5f));
    char text[] = "PRINT,part=#1";
    char *result = ngc_process_comment(text);
    CHECK(result != NULL);
    CHECK(strcmp(result, "part=7.500") == 0);
    free(result);
    return EXIT_SUCCESS;
}
