#include "support/engine_host.h"
#include "ngc_expr.h"
#include "check.h"

int main(void)
{
    char line[] = "N42X1";
    uint_fast8_t pos = 1;
    uint32_t value = 123;
    CHECK(ngc_read_integer_unsigned(line, &pos, &value) == Status_OK);
    CHECK(value == 42U);
    CHECK(pos == 3);
    return EXIT_SUCCESS;
}
