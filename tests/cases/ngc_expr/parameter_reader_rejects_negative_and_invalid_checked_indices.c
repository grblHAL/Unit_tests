#include "support/expression_eval_host.h"

int main(void)
{
    engine_parser_prepare();
    char negative[] = "#-1"; uint_fast8_t pos = 0; float value = 0;
    CHECK(ngc_read_parameter(negative, &pos, &value, true) == Status_GcodeValueOutOfRange);
    char missing[] = "#99999"; pos = 0;
    CHECK(ngc_read_parameter(missing, &pos, &value, true) == Status_GcodeValueOutOfRange);
    return EXIT_SUCCESS;
}
