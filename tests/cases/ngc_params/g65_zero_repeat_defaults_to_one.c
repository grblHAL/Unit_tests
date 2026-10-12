#include "support/macro_parser_host.h"
#include "check.h"

int main(void)
{
    prepare_macro_parser();
    CHECK(macro_block("G65P100L0") == Status_OK);
    CHECK(macro_calls == 1);
    CHECK(macro_repeats == 1);
    CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
