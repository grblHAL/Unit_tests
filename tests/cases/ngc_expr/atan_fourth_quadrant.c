#include "support/engine_host.h"
#include "ngc_expr.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char text[] = "[ATAN[-1]/[1]]";
    uint_fast8_t pos = 0;
    float value = 0;
    CHECK(ngc_eval_expression(text, &pos, &value) == Status_OK);
    CHECK(pos == strlen(text));
    NEAR(value, -45.0f);
    return EXIT_SUCCESS;
}
