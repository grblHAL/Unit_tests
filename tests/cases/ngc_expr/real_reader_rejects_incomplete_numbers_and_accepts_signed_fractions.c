#include "support/engine_host.h"
#include "ngc_expr.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();
    const char *invalid[] = {"", "+", "-", ".", "+.", "-.", "a"};
    for(unsigned i = 0; i < sizeof(invalid) / sizeof(invalid[0]); i++) {
        char text[8]; strcpy(text, invalid[i]);
        uint_fast8_t pos = 0;
        float value = 17;
        CHECK(ngc_read_real_value(text, &pos, &value) ==
            (i == 0 ? Status_ExpressionSyntaxError : Status_BadNumberFormat));
    }
    char positive[] = "+.5X", negative[] = "-.25Y";
    uint_fast8_t pos = 0;
    float value = 0;
    CHECK(ngc_read_real_value(positive, &pos, &value) == Status_OK);
    NEAR(value, .5f);
    CHECK(positive[pos] == 'X');
    pos = 0;
    CHECK(ngc_read_real_value(negative, &pos, &value) == Status_OK);
    NEAR(value, -.25f);
    CHECK(negative[pos] == 'Y');
    return EXIT_SUCCESS;
}
