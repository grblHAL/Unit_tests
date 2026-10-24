#include "support/engine_host.h"
#include "ngc_expr.h"
#include "check.h"
int main(void)
{
    engine_parser_prepare();
    char input[] = "AX[1]";
    uint_fast8_t pos = 0;
    float value = 0;
    CHECK(ngc_read_real_value(input, &pos, &value) == Status_ExpressionUknownOp);
    pos = 0;
    value = NAN; /* An output parameter need not contain a valid prior result. */
    status_code_t status = ngc_read_real_value(input, &pos, &value);
    fprintf(stderr, "Malformed unary with nonfinite output: status=%u expected=%u\n",
        (unsigned)status, (unsigned)Status_ExpressionUknownOp);
    CHECK(status == Status_ExpressionUknownOp);
    return EXIT_SUCCESS;
}
