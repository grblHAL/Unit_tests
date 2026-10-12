#include "support/engine_host.h"
#include "ngc_expr.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char name[] = "part";
    CHECK(ngc_named_param_set(name, 7));
    char text[] = "[EXISTS[#<part>]]";
    uint_fast8_t pos = 0;
    float value = -1;
    CHECK(ngc_eval_expression(text, &pos, &value) == Status_OK);
    CHECK(pos == strlen(text));
    NEAR(value, 1.0f);
    CHECK(strcmp(text, "[EXISTS[#<part>]]") == 0);
    return EXIT_SUCCESS;
}
