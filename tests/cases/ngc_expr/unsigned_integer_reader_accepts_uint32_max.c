#include "support/engine_host.h"
#include "ngc_expr.h"
#include "check.h"

int main(void)
{
    char line[] = "4294967295";
    uint_fast8_t pos = 0;
    uint32_t value = 123;
    CHECK(ngc_read_integer_unsigned(line, &pos, &value) == Status_OK);
    CHECK(value == 4294967295U);
    CHECK(pos == 10);
    return EXIT_SUCCESS;
}
