#include <string.h>
#include "support/engine_host.h"
#include "ngc_expr.h"
#include "check.h"
static float eval(char *text) {
    uint_fast8_t pos = 0; float value = 0;
    CHECK(ngc_eval_expression(text, &pos, &value) == Status_OK);
    CHECK(pos == strlen(text)); return value;
}
int main(void)
{
    engine_parser_prepare();
    char expression0[] = "[2LT3]"; NEAR(eval(expression0), 1);
    char expression1[] = "[3GE3]"; NEAR(eval(expression1), 1);
    char expression2[] = "[3GT4]"; NEAR(eval(expression2), 0);
    char expression3[] = "[2EQ2]"; NEAR(eval(expression3), 1);
    char expression4[] = "[2NE3]"; NEAR(eval(expression4), 1);
    return EXIT_SUCCESS;
}
