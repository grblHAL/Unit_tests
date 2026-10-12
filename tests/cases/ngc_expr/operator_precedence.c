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
    char expression0[] = "[2+3*4]"; NEAR(eval(expression0), 14);
    char expression1[] = "[12/3+2]"; NEAR(eval(expression1), 6);
    return EXIT_SUCCESS;
}
