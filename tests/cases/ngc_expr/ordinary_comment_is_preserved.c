#include "support/engine_host.h"
#include "ngc_expr.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();

    char text[] = "ordinary comment";
    char *result = ngc_process_comment(text);
    CHECK(result == NULL);
    CHECK(strcmp(text, "ordinary comment") == 0);
    return EXIT_SUCCESS;
}
