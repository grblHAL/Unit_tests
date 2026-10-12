#include "support/flow_host.h"
#include "support/system_command_host.h"
#include "ngc_expr.h"
#include "check.h"
int main(void)
{
    prepare_system_command();
    char expression[] = "[1/0]";
    uint_fast8_t pos = 0;
    float value;
    CHECK(ngc_eval_expression(expression, &pos, &value) == Status_ExpressionDivideByZero);
    status_code_t status = flow_command(10, "ERROR[1/0]");
    fprintf(stderr, "Expression error status: %u (expected %u)\n", (unsigned)status, (unsigned)Status_ExpressionDivideByZero);
    CHECK(status == Status_ExpressionDivideByZero);
    CHECK(sys.alarm == Alarm_None);
    CHECK(state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
