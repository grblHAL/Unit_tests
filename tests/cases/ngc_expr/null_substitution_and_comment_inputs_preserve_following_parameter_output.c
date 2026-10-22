#include "support/engine_host.h"
#include "ngc_expr.h"
#include "ngc_params.h"
#include "check.h"
#include <string.h>
int main(void)
{
    engine_parser_prepare();
    CHECK(ngc_param_set(1, 7.5f));
    CHECK(ngc_substitute_parameters(NULL) == NULL);
    CHECK(ngc_process_comment(NULL) == NULL);
    float value;
    CHECK(ngc_param_get(1, &value));
    NEAR(value, 7.5f);
    char text[] = "part=#1";
    char *result = ngc_substitute_parameters(text);
    CHECK(result && strcmp(result, "part=7.500") == 0);
    free(result);
    return EXIT_SUCCESS;
}
