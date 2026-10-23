#include "support/expression_eval_host.h"

int main(void)
{
    engine_parser_prepare();
    const char *invalid[] = {"[AX[1]]", "[CX[1]]", "[EX[1]]", "[FX[1]]", "[LX[1]]",
                             "[RX[1]]", "[SX[1]]", "[TX[1]]", "[PX[1]]", "[ZX[1]]"};
    for(unsigned i = 0; i < sizeof(invalid) / sizeof(invalid[0]); i++) {
        char text[96]; strcpy(text, invalid[i]);
        uint_fast8_t pos = 0; float value = 0;
        status_code_t status = ngc_eval_expression(text, &pos, &value);
        fprintf(stderr, "%s status=%u expected=%u pos=%u\n", invalid[i],
            (unsigned)status, (unsigned)Status_ExpressionUknownOp, (unsigned)pos);
        CHECK(status == Status_ExpressionUknownOp);
    }
    return EXIT_SUCCESS;
}
