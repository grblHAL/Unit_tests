#include "support/expression_eval_host.h"

int main(void)
{
    engine_parser_prepare();
    NEAR(evaluate_complete_expression("[2LE2]"), 1);
    NEAR(evaluate_complete_expression("[1LE2]"), 1);
    NEAR(evaluate_complete_expression("[3LE2]"), 0);
    return EXIT_SUCCESS;
}
