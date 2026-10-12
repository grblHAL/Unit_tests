#include <string.h>
#include "support/engine_host.h"
#include "ngc_expr.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare(); char text[] = "[SQRT[-1]]"; uint_fast8_t pos = 0; float value = 0;
    CHECK(ngc_eval_expression(text, &pos, &value) == Status_ExpressionArgumentOutOfRange);
    return EXIT_SUCCESS;
}
