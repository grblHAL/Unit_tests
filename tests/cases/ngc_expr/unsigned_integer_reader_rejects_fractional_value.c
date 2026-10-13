#include "support/engine_host.h"
#include "ngc_expr.h"
#include "check.h"

int main(void)
{
    char line[] = "42.5";
    uint_fast8_t pos = 0;
    uint32_t value = 123;
    CHECK(ngc_read_integer_unsigned(line, &pos, &value) == Status_GcodeCommandValueNotInteger);
    CHECK(value == 123U);
    CHECK(pos == 0);
    return EXIT_SUCCESS;
}
