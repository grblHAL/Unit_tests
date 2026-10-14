#include "support/expression_eval_host.h"

int main(void)
{
    engine_parser_prepare();
    const char *invalid[] = {"[AX[1]]", "[CX[1]]", "[EX[1]]", "[FX[1]]", "[LX[1]]",
                             "[RX[1]]", "[SX[1]]", "[TX[1]]", "[PX[1]]", "[ZX[1]]"};
    for(unsigned i = 0; i < sizeof(invalid) / sizeof(invalid[0]); i++)
        reject_expression(invalid[i], Status_ExpressionUknownOp);
    return EXIT_SUCCESS;
}
