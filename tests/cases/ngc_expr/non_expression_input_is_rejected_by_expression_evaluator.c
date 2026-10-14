#include "support/expression_eval_host.h"

int main(void)
{
    engine_parser_prepare();
    reject_expression("42", Status_GcodeUnsupportedCommand);
    reject_expression("SIN[30]", Status_GcodeUnsupportedCommand);
    reject_expression("", Status_GcodeUnsupportedCommand);
    return EXIT_SUCCESS;
}
