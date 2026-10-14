#include "support/expression_eval_host.h"
#include "ngc_params.h"

int main(void)
{
    engine_parser_prepare();
    CHECK(ngc_param_set(1, 7.5f));
    char text[] = "bad=%.xf; value=%.1f#1";
    char *result = ngc_substitute_parameters(text);
    CHECK(result != NULL);
    CHECK(strcmp(result, "bad=%.xf; value=7.5") == 0);
    free(result);
    return EXIT_SUCCESS;
}
