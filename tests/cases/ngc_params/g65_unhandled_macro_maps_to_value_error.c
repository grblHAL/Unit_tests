#include "support/macro_parser_host.h"
#include "check.h"

int main(void)
{
    prepare_macro_parser();
    macro_result = Status_Unhandled;
    CHECK(macro_block("G65P100") == Status_GcodeValueOutOfRange);
    CHECK(macro_calls == 1);
    CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
