#include "support/expression_eval_host.h"

int main(void)
{
    engine_parser_prepare();
    const char *invalid[] = {"[1AX2]", "[1MX2]", "[1OX2]", "[1XX2]",
                             "[1EX2]", "[1NX2]", "[1GX2]", "[1LX2]"};
    for(unsigned i = 0; i < sizeof(invalid) / sizeof(invalid[0]); i++)
        reject_expression(invalid[i], Status_ExpressionUknownOp);
    return EXIT_SUCCESS;
}
