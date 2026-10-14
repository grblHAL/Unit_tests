#include "support/expression_eval_host.h"

int main(void)
{
    engine_parser_prepare();
    NEAR(evaluate_complete_expression("[-2.5LE-2.25]"), 1);
    NEAR(evaluate_complete_expression("[-2.25LE-2.5]"), 0);
    NEAR(evaluate_complete_expression("[-2.5LE-2.5]"), 1);
    return EXIT_SUCCESS;
}
