#include "support/expression_eval_host.h"

int main(void)
{
    engine_parser_prepare();
    NEAR(evaluate_complete_expression("[+[2+3]]"), 5);
    NEAR(evaluate_complete_expression("[+ABS[-3]]"), 3);
    NEAR(evaluate_complete_expression("[+[2]*3]"), 6);
    return EXIT_SUCCESS;
}
