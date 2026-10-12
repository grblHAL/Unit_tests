#include "support/macro_parser_host.h"
#include "check.h"

int main(void)
{
    prepare_macro_parser();
    CHECK(macro_block("N42G65P100L3") == Status_OK);
    CHECK(macro_calls == 1);
    CHECK(called_macro == 100);
    CHECK(macro_line == 42);
    CHECK(macro_repeats == 3);
    CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
