#include "support/expression_eval_host.h"

int main(void)
{
    engine_parser_prepare();
    NEAR(evaluate_complete_expression("[1+2LE2*2]"), 1);
    NEAR(evaluate_complete_expression("[2*3LE1+2]"), 0);
    NEAR(evaluate_complete_expression("[[1+2]LE[6/2]]"), 1);
    return EXIT_SUCCESS;
}
